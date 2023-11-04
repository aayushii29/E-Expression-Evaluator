/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
// #include "exprtreenode.h"
// #include "ulimitedrational.cpp"
// #include "ulimitedint.cpp"
// #include <iostream>
using namespace std;
ExprTreeNode::ExprTreeNode(){
    type = "Surprise MFs";
    val = nullptr;
    evaluated_value = nullptr;
    id = "";
    left = nullptr;
    right = nullptr;
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedInt* v){
    type = t;
    UnlimitedInt* One = new UnlimitedInt(1);
    val = new UnlimitedRational(v,One);
    evaluated_value = nullptr;
    // id = t;
    left = nullptr;
    right = nullptr;    
}
ExprTreeNode::ExprTreeNode(string t, UnlimitedRational* v){
    type = t;
    // UnlimitedInt* One = new UnlimitedInt(1);
    val = v;
    evaluated_value = nullptr;
    // id = t;
    left = nullptr;
    right = nullptr;    
}
ExprTreeNode::~ExprTreeNode(){
    delete val;
    delete evaluated_value;
}