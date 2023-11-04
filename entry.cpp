/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"
using namespace std;

SymEntry::SymEntry(){
    key = " ";
    val = nullptr;
    left = nullptr;
    right = nullptr;
}
SymEntry::SymEntry(string k, UnlimitedRational* v){
    key = k;
    left = nullptr;
    right = nullptr;
    UnlimitedRational* temp = new UnlimitedRational(new UnlimitedInt(v->get_p_str()),new UnlimitedInt(v->get_q_str()));
    val = temp;
}

SymEntry::~SymEntry(){
    delete val;
}