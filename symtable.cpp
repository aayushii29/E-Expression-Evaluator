/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// #include <iostream>
// #include "entry.cpp"
// #include "ulimitedint.cpp"
// #include "ulimitedrational.cpp"
// #include <string>
using namespace std;

SymbolTable::SymbolTable(){
    size = 0;
    root = nullptr;
}

void Delete(SymEntry* s){
    if(s->right != nullptr){
        Delete(s->right);
    }
    if(s->left != nullptr){
        Delete(s->left);
    }
    delete s;
}
SymbolTable::~SymbolTable(){
    Delete(root);
}

    // Insert a key value pair in the symbol table
void SymbolTable::insert(string k, UnlimitedRational* v){
    SymEntry* r = get_root();
    SymEntry* newEntry = new SymEntry(k,v);
    if(r == nullptr){
        root = newEntry;
        size++;
    }
    else{
        SymEntry* current = r;
        while(current != nullptr){
            if(current->key > k){
                if(current->left == nullptr){
                    current->left = newEntry;
                    size++;
                }
                else{
                    current = current->left;
                }
            }
            else if(current->key < k){
                if(current->right == nullptr){
                    current->right = newEntry;
                    size++;
                }
                else{
                    current = current->right;
                }
            }
            else{
                break;
            }
        }
    }


}
// SymEntry* parent(SymEntry* n,SymEntry* root){
//     // SymEntry* current = SymbolTable::get_root();
//     SymEntry* current = root;
//     while(current != nullptr && current->right->key!= n->key && current->left->key != n->key ){
//             if(current->key >= n->key){
//                 current = current->left;
//             }
//             else{
//                 current = current->right;
//             }
//         }
//     return current;
// }

SymEntry* findMin(SymEntry* n){
        while(n->left != nullptr){
            n = n->left;
        }
        return n;
}

    // Remove a key (and value) in the symbol table
void SymbolTable::remove(string k){
    //    UnlimitedRational* u = search(k);
       SymEntry* current = get_root();
    //    SymEntry* r = nullptr;
       while(current != nullptr){
            if(current->key > k){
                    if(current->left != nullptr){
                        current = current->left;
                    }
                }
            else if(current->key < k){
                if(current->right != nullptr){
                    current = current->right;
                }
            }
            else{
               break;
            }
        }
        if(current->left == nullptr && current ->right == nullptr){
            delete current;
        }
        else if(current->left != nullptr && current->right ==  nullptr){
            SymEntry* temp = current->left;
            current = temp;
            delete current->left;
        }
        else if(current->right != nullptr && current->left == nullptr){
            SymEntry* temp = current->right;
            current = temp;
            delete current->right;
        }
        else{
            SymEntry* successor = findMin(current->right);
            SymEntry* temp = successor;
            remove(successor->key);
            current->key = temp->key;
            current->val = temp->val;
        }
       }

    // Find the val corresponding to the key in the symbol table
    UnlimitedRational* SymbolTable::search(string k){
        SymEntry* r = get_root();
        if(r->val == nullptr){
            return nullptr;
        }
        else{
            SymEntry* current = r;
            while (current != nullptr){
                if(current->key > k){
                    if(current->left != nullptr){
                        current = current->left;
                    }
                    else{
                        return nullptr;
                    }
                }
                else if(current->key < k){
                    if(current->right != nullptr){
                        current = current->right;
                    }
                    else{
                        return nullptr;
                    }
                }
                else{
                    return current->val;
                }
            }
            
        }
        return r->val;
    }

    // Get size
    int SymbolTable::get_size(){
        return size;
    }

    // Get root 
    SymEntry* SymbolTable::get_root(){
        return root;
    }
