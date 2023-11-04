/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "evaluator.h"
// #include <iostream>
// #include "symtable.cpp"
// #include "exprtreenode.cpp"
// #include "ulimitedint.cpp"
// #include "ulimitedrational.cpp"
// #include "entry.cpp"
Evaluator::Evaluator(){
    expr_trees={};
    symtable=new SymbolTable();
}
Evaluator::~Evaluator(){
    delete symtable;
}
UnlimitedRational* evaluate_subtree(ExprTreeNode* R){
//    cout<<"hepler evalstart"<<endl;
        // cout<<R->type<<endl;
        if(R->type == "ADD"){
            // cout<<"addf"<<endl;
            R->evaluated_value = UnlimitedRational::add(evaluate_subtree(R->left),evaluate_subtree(R->right));
            //  cout<<R->evaluated_value->get_frac_str()<<endl;
            //  cout<<"addb"<<endl;
            
        }
        else if(R->type == "SUB"){
            // cout<<"sub"<<endl;
            R->evaluated_value = UnlimitedRational::sub(evaluate_subtree(R->left),evaluate_subtree(R->right));
            // cout<<R->evaluated_value->get_frac_str()<<endl;
        }
        else if(R->type == "MUL"){
            // cout<<"mul"<<endl;
            R->evaluated_value = UnlimitedRational::mul(evaluate_subtree(R->left),evaluate_subtree(R->right));
            // cout<<R->evaluated_value->get_frac_str()<<endl;
        }

        else if(R->type == "DIV"){
            //  cout<<"divf"<<endl;
            R->evaluated_value = UnlimitedRational::div(evaluate_subtree(R->left),evaluate_subtree(R->right));
            // cout<<R->evaluated_value->get_frac_str()<<endl;
            // cout<<"divb"<<endl;
           
        }
        else if(R->type == "VAR"){
            // cout<<"var"<<endl;
            R->evaluated_value = R->val;
            // cout<<R->evaluated_value->get_frac_str()<<endl;
        }
        else{
            //  cout<<"val"<<endl;
            R->evaluated_value = R->val;
            // cout<<R->evaluated_value->get_frac_str()<<endl;
        }
        
        UnlimitedRational* temp = new UnlimitedRational(R->evaluated_value->get_p(),R->evaluated_value->get_q());
        R->evaluated_value=temp;
       
        // cout<<" final ans"<<endl;/
        //  cout<<temp->get_frac_str()<<endl;
        // cout<<"helper evalend"<<endl;
        return temp;

}
void Evaluator::parse(vector<string> code){
    ExprTreeNode* ROOT = new ExprTreeNode();
    ROOT->id = code[1];

    // cout<<ROOT->id<<endl;
    ExprTreeNode* v = new ExprTreeNode();
    v->type = "VAR";
    v->id = code[0];    

    vector<ExprTreeNode*> EMPTYNODES;
    vector<ExprTreeNode*> OPERATORS;

    ExprTreeNode* eroot = new ExprTreeNode();
    EMPTYNODES.push_back(eroot);

    ROOT->right = eroot;
    ROOT->left = v;

    // std::cout<<"Parse"<<endl;
    
    for(auto i = static_cast<std::vector<std::__cxx11::basic_string<char>>::size_type>(2) ; i < code.size(); i++){
         
        //  cout<<code[i]<<endl;
        if(code[i] == "("){

            // std::cout<<"("<<endl;
            eroot->left = new ExprTreeNode();
            EMPTYNODES.push_back(eroot->left);
            OPERATORS.push_back(eroot);
            eroot = eroot->left;
            
        }
        else if(code[i] == "+" || code[i] == "-" || code[i] == "/" || code[i] == "*" || code[i] == "%"){
            
            if(code[i] == "+"){

                eroot->type = "ADD";
                // std::cout<<eroot->type<<endl;
            }

            else if(code[i] == "-"){

                eroot->type = "SUB";
                // std::cout<<eroot->type<<endl;
            }

            else if(code[i] == "*"){

                eroot->type = "MUL";
                // std::cout<<eroot->type<<endl;
            }

            else if(code[i] == "/"){

                eroot->type = "DIV";
                // std::cout<<eroot->type<<endl/;
            }

            // OPERATORS.push_back(eroot);
            // EMPTYNODES.pop_back();
            eroot->id = code[i];
            eroot->right = new ExprTreeNode();
            EMPTYNODES.pop_back();
            EMPTYNODES.push_back(eroot->right);
            eroot = eroot->right;
        }
        else if(code[i] == ")"){
            //  EMPTYNODES.pop_back();
             
             OPERATORS.pop_back();
             eroot = OPERATORS.back();
            //  std::cout<<")"<<endl;
        }
        else{
            // Val
            if(code[i][0] == '0' || code[i][0] == '1' || code[i][0] == '2' || code[i][0] == '3' || code[i][0] == '4' || code[i][0] == '5' || code[i][0] == '6' || code[i][0] == '7' || code[i][0] == '8' || code[i][0] == '9' || code[i] == '-'){
                EMPTYNODES.pop_back();
                eroot->type = "VAL";
                eroot->id = code[i];
                UnlimitedInt* p = new UnlimitedInt(code[i]);
                UnlimitedInt* one = new UnlimitedInt(1);
                eroot->val = new UnlimitedRational(p,one);
                if(OPERATORS.size() > 0){
                    eroot = OPERATORS.back();
                }
                // std::cout<<"VAL"<<endl;
            }
            else{
                // VAR
                // std::cout<<code[i]<<endl;
                EMPTYNODES.pop_back();
                eroot->type = "VAR";
                eroot->id = code[i];
                eroot->val = symtable->search(eroot->id);
                if(OPERATORS.size() > 0){
                    eroot = OPERATORS.back();
                }
                
            }
        }
    }
    // std::cout<<"Parse end"<<endl;
    expr_trees.push_back(ROOT);
    // std::cout<<expr_trees.back()->right->val->UnlimitedRational::get_frac_str()<<endl;
}


void Evaluator::eval(){
    // UnlimitedRational* k= HelperEval(expr_trees[expr_trees.size()-1]->right);
    // symtable->insert(expr_trees[expr_trees.size()-1]->left->id,k);
    // v := E last element is the root node := , we need to calculate the value of its right subtree which is the val of variable v 
    // We then store key value pair (v,Eval(E)) in the Symbol Table
    // cout<<"eval staert"<<endl;
    ExprTreeNode* R  = expr_trees.back();
    // cout<<"eval staert"<<endl;
    string v = R->left->id; // The name of the variable , to store in Symbol Table
    // cout<<"eval staert"<<endl;
    ExprTreeNode* E = R->right; // We will evaluate the value of this node , which is the value of v
    // cout<<"eval staert"<<endl;
    UnlimitedRational* x = evaluate_subtree(E);
    // cout<<"eval staert"<<endl;
    // cout<<"eval ewnd"<<endl;
    symtable->insert(v,x);

}
// #include<iostream>
// using namespace std;
// int main(){

//     vector<string> a1={"a",":=","5"};
//     vector<string> a2={"b",":=","(","(","a","+","3",")","*","2",")"};
//     vector<string> a3={"c",":=","(","(","(","a","+","b",")","*","3",")","-","7",")"};
//     vector<string> a4={"d",":=","(","(","a","/","6",")","*","(","b","/","c",")",")"};
//     vector<string> a5={"e",":=","d"};
//     vector<string> a6={"f",":=","(","e","+","5",")"};
//     Evaluator* E = new Evaluator();
//     cout<<"1"<<endl;
//     E->parse(a1);
//         // cout<<"-1"<<endl;
//     // cout<<"Yo"<<endl;
//     //  cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     E->eval();
//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"2"<<endl;
//     E->parse(a2);
    
//     E->eval();

//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"3"<<endl;
//     E->parse(a3);
//     E->eval();
//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"4"<<endl;
//     E->parse(a4);
//     E->eval();
//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"5"<<endl;
//     E->parse(a5);
//     E->eval();
//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"6"<<endl;
//     E->parse(a6);
//     E->eval();
//     cout<<E->expr_trees[E->expr_trees.size()-1]->right->id<<endl;
//     cout<<"7"<<endl;
//     cout<<E->symtable->search("b")->get_frac_str()<<endl;
// }
