#include "ulimitedrational.h"
// #include "ulimitedint.cpp" 
// #include <iostream>

UnlimitedRational::UnlimitedRational() {
    p = new UnlimitedInt(1);
    q = new UnlimitedInt(1);
}
int compareR(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* a = i1->get_array();
    int* b = i2->get_array();
    int n1 = i1->get_size();
    int n2 = i2->get_size();
    if(n1>n2){
        return 1;
    }
    else if(n1<n2){
        return -1;
    }
    else{
        for(int i=0; i<n1; i++){
            if(a[i]>b[i]){
                return 1;
            }
            else if(b[i]>a[i]){
                return -1;
            }
        }
    }
    return 1; 
}
UnlimitedInt* mygcd(UnlimitedInt* i1, UnlimitedInt* i2){
    
    // UnlimitedInt* minusone = new UnlimitedInt(-1);
    if(i1->get_sign() == -1){
        UnlimitedInt* temp = new UnlimitedInt(i1->get_array(),i1->get_capacity(), -1 * i1->get_sign(),i1->get_size());
        i1 = temp;
    }
    if(i2->get_sign() == -1){
        UnlimitedInt* temp = new UnlimitedInt(i2->get_array(),i2->get_capacity(), -1 * i2->get_sign(),i2->get_size());
        i2 = temp;
    }
    // a >= b by assumption, if not we swap
    UnlimitedInt* temp = nullptr;
    if (compareR(i1,i2) < 0) {
        temp = i1;
        i1 = i2;
        i2 = temp;
    }


    UnlimitedInt* remainder = nullptr;
    while (i2->UnlimitedInt::to_string() != "0") {
        remainder = UnlimitedInt::mod(i1,i2);
        i1 = i2;
        i2 = remainder;
    }

    int m = i1->get_size();
    int* c = new int [m]; 

    for(int i = 0 ; i < m; i++){
        c[i] = i1->get_array()[i];
    }

    return new UnlimitedInt(c,m,1,m);
}
UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den) {
    if(den->UnlimitedInt::to_string() == "0"){
        p = new UnlimitedInt(0);
        q = new UnlimitedInt(0);
    }
    else{
        if(num->UnlimitedInt::to_string() == "0" ){
            p = new UnlimitedInt(0);
            q = new UnlimitedInt(1);
        }
        else{
            UnlimitedInt* gcd = mygcd(num,den);

            p = UnlimitedInt::div(num,gcd);
            q = UnlimitedInt::div(den,gcd);
            delete gcd;
        }
        
    }
}

UnlimitedRational::~UnlimitedRational() {
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p() {
    return p;
}

UnlimitedInt* UnlimitedRational::get_q() {
    return q;
}

string UnlimitedRational::get_p_str() {
    return p->UnlimitedInt::to_string();
}

string UnlimitedRational::get_q_str() {
    return q->UnlimitedInt::to_string();
}

string UnlimitedRational::get_frac_str() {
    return p->UnlimitedInt::to_string() + "/" + q->UnlimitedInt::to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* n1 = r1->get_p();
    UnlimitedInt* d1 = r1->get_q();
    UnlimitedInt* n2 = r2->get_p();
    UnlimitedInt* d2 = r2->get_q();
    UnlimitedInt* z = new UnlimitedInt("0");
    if(d1->to_string() == "0" || d2->to_string() == "0"){
        return new UnlimitedRational(z,z);
    }
    UnlimitedInt* x = UnlimitedInt::mul(n1, d2);
    UnlimitedInt* y = UnlimitedInt::mul(n2, d1);
    UnlimitedInt* new_num = UnlimitedInt::add(x,y);
    UnlimitedInt* new_den = UnlimitedInt::mul(d1, d2);
    UnlimitedRational* ans = new UnlimitedRational(new_num, new_den);

    delete x;
    delete y;
    delete new_num;
    delete new_den;
    return ans;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* n1 = r1->get_p();
    UnlimitedInt* d1 = r1->get_q();
    UnlimitedInt* n2 = r2->get_p();
    UnlimitedInt* d2 = r2->get_q();
        UnlimitedInt* z = new UnlimitedInt("0");
    if(d1->to_string() == "0" || d2->to_string() == "0"){
        return new UnlimitedRational(z,z);
    }
    UnlimitedInt* x = UnlimitedInt::mul(n1, d2);
    UnlimitedInt* y = UnlimitedInt::mul(n2, d1);
    UnlimitedInt* new_num = UnlimitedInt::sub(x,y);
    UnlimitedInt* new_den = UnlimitedInt::mul(d1, d2);
    UnlimitedRational* ans = new UnlimitedRational(new_num, new_den);

    delete x;
    delete y;
    delete new_num;
    delete new_den;
    return ans;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* n1 = r1->get_p();
    UnlimitedInt* n2 = r2->get_p();
    UnlimitedInt* d1 = r1->get_q();
    UnlimitedInt* d2 = r2->get_q();
    UnlimitedInt* z = new UnlimitedInt("0");
    if(d1->to_string() == "0" || d2->to_string() == "0"){
        return new UnlimitedRational(z,z);
    }
    UnlimitedInt* new_num = UnlimitedInt::mul(n1, n2);
    UnlimitedInt* new_den =  UnlimitedInt::mul(d1, d2);

    UnlimitedRational* ans = new UnlimitedRational(new_num, new_den);

    delete new_num;
    delete new_den;

    return ans;
}
UnlimitedRational* UnlimitedRational::div(UnlimitedRational* r1, UnlimitedRational* r2) {
    UnlimitedInt* n1 = r1->get_p();
    UnlimitedInt* n2 = r2->get_p();
    UnlimitedInt* d1 = r1->get_q();
    UnlimitedInt* d2 = r2->get_q();
    UnlimitedInt* z = new UnlimitedInt("0");
    if(d1->to_string() == "0" || d2->to_string() == "0"){
        return new UnlimitedRational(z,z);
    }
    UnlimitedInt* new_num = UnlimitedInt::mul(n1, d2);
    UnlimitedInt* new_den =  UnlimitedInt::mul(n2, d1);
    
    UnlimitedRational* ans = new UnlimitedRational(new_num, new_den);

    delete new_num;
    delete new_den;

return ans;
}