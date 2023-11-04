/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>
UnlimitedInt::UnlimitedInt(){
    size = 0;
    sign = 1;
    capacity = 1;  
    unlimited_int = new int[capacity];
    unlimited_int[0] = 0;
}
UnlimitedInt::UnlimitedInt(string s){
    capacity = s.length();
    unlimited_int = new int[capacity];
    int temp;
    if (s[0] == '-') {
        for (std::__cxx11::basic_string<char>::size_type i = 0; i < s.length() - 1; i++) {
            temp = s[i + 1] - '0';
            unlimited_int[i] = temp;
        }
        sign = -1;
        size = s.length() - 1;
    } else {
        for (std::__cxx11::basic_string<char>::size_type i = 0; i < s.length(); i++) {
            temp = s[i] - '0'; 
            unlimited_int[i] = temp;
        }
        sign = 1;
        size = s.length();
    }
    if(s[0]=='0' && capacity==1){
        unlimited_int[0]=0;
        size=1;
        sign=1;
    }
}    


UnlimitedInt::UnlimitedInt(int i){
    if(i == 0){
            sign = 1;
            size = 1; 
            capacity = size;
            unlimited_int = new int[capacity];
            unlimited_int[0] = 0;
    }
    else{
        if(i >= 0){
            sign = 1;
        }
        else{
            sign = -1;
        }
        size = 0;
        int n = i;
        while (n != 0) {
            n /= 10;
            size++;
        }
        capacity = size;
        unlimited_int = new int[capacity];
        int j = size - 1;
        while(i != 0){
            unlimited_int[j] = abs(i % 10);
            i = i / 10;
            j--;
        }
    }

}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz){
    capacity=cap;
    size=sz;
    sign=sgn;
    int* k=new int [sz];
    for(int i=0;i<sz; i++){
        k[i]=ulimited_int[i];
    }
    unlimited_int=k;
    
}
int compare(UnlimitedInt* i1, UnlimitedInt* i2) {
    int* a = i1->get_array();
    int* b = i2->get_array();
    int n1 = i1->get_size();
    int n2 = i2->get_size();

    if (n1 > n2) {
        return 1; 
    } else if (n2 > n1) {
        return -1; 
    } else {
        for (int i = 0; i < n1; i++) {
            if (a[i] > b[i]) {
                return 1; 
            } else if (b[i] > a[i]) {
                return -1; 
            }
        }
        return 0; 
    }
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

    // Return the size of the unlimited int
int UnlimitedInt::get_size(){
    return size;
}

    // Return the unlimited_int array
int* UnlimitedInt::get_array(){
    return unlimited_int;
} 

    // Get sign
int UnlimitedInt::get_sign(){
    return sign;
}

    // Get capacity 
int UnlimitedInt::get_capacity(){
    return capacity;
}



UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->get_sign() != i2->get_sign()){
        UnlimitedInt* minusone = new UnlimitedInt(-1); 
        if(i1->get_sign() == 1 ){
            //  a + -b = a - b
            // cout<<i2->get_sign()<<endl;
            UnlimitedInt* t2 = mul(i2,minusone);
            // cout<<i2->get_sign()<<endl;
            UnlimitedInt* temp = sub(i1,t2);
            return temp;
        }
        else{
            //  -a + b = +b - +a
            UnlimitedInt* t1 = mul(i1,minusone);
            UnlimitedInt* tempo = sub(i2,t1);
            return tempo;
        }
    }
   
    else  {
        int* a = i1->get_array();
        int* b = i2->get_array();
        int n1 = i1->get_size();
        int n2 = i2->get_size();
        int max_len = std::max(n1, n2);
        int* c = new int[max_len + 1];
    // UnlimitedInt* i3 = nullptr; // Initialize to nullptr

        int newSign = i1->get_sign();
        int carry = 0;
        int k = 0;
        int i = n1 - 1;
        int j = n2 - 1;
        int sum =0;
        while (i >= 0 || j >= 0) {
            sum = carry;
            if (i >= 0) {
                sum += a[i];
                i--;
            }
            if (j >= 0) {
                sum += b[j];
                j--;
            }

            c[k] = sum % 10;
            carry = sum / 10;
            k++;
        }

        if (carry > 0) {
            c[k] = carry ;
            k++;
            
        }
        // else{
        //     c[k]=0;
        //     k++;
        // }
        // for(int i=0;i<k ; i++){
        //     cout<<c[i];
        // }
        // cout<<endl;
        int* dear = new int [k]; 
        for(int i = 1;i <= k; i++){
            dear[i-1]=c[k - i];
        }
        // for(int i=0;i<k ; i++){
        //     cout<<dear[i];
        // }
        // cout<<endl;
        delete[] c;
        int firstNonZeroIndex = 0;
        while (firstNonZeroIndex < k && dear[firstNonZeroIndex] == 0) {
            firstNonZeroIndex++;
        }
        int* ans =new int [k - firstNonZeroIndex ];
        for (int i = firstNonZeroIndex; i < k; i++) {
            ans[i - firstNonZeroIndex] = dear[i];
        }
        // k = n1+1-firstNonZeroIndex;
        delete[] dear;
        
        
        return new UnlimitedInt(ans, k - firstNonZeroIndex, newSign, k - firstNonZeroIndex);
}
return new UnlimitedInt("0");
}


UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->to_string() == i2->to_string()){
        return new UnlimitedInt("0");
    }
    else if(i1->get_sign() != i2->get_sign()){
            UnlimitedInt* minusone = new UnlimitedInt("-1"); 
            if(i1->get_sign() == 1 && i2->get_sign() == -1){
                //  a - -b = a + b
                // cout<<i2->get_sign()<<endl;
                UnlimitedInt* t2 = new  UnlimitedInt();
                t2 = mul(i2,minusone);
                // cout<<i2->get_sign()<<endl;
                UnlimitedInt* temp = new UnlimitedInt();
                temp = add(t2,i1);
                return temp;
            }
            else{
                //  -a - b = -1(b + a)  -1 - 2 = -3 
                UnlimitedInt* t1 = new UnlimitedInt();
                t1 = mul(i1,minusone); // 1
                UnlimitedInt* temp = mul(minusone,add(i2,t1)); // 2+1
                return temp;
            }
        }
    else{ 
        // a - b = 3 - 5 = 5 -3
         int newSign = i1->get_sign();
        if(compare(i1,i2) == -1){
            UnlimitedInt* temp = i1;
            i1 = i2;
            i2 = temp;
            newSign = -1 * newSign;
        }
        int* a = i1->get_array();
        int* b = i2->get_array();
        int n1 = i1->get_size();
        int n2 = i2->get_size();
        // int max_len = std::max(n1, n2);
        
        
        int* c = new int[n1 + 1];
        int carry = 0;
        int k = 0;
        int i = n1 - 1;
        int j = n2 - 1;
        int sum = 0;
        while (i >= 0 || j >= 0) {
            sum = carry;
            if (i >= 0) {
                sum += a[i];
                i--;
            }
            if (j >= 0) {
                sum -= b[j];
                j--;
            }
             if(sum >= 0){
                carry = 0;
            }
            else{
                sum += 10;
                carry = -1;
            }
            c[k] = sum ;
            k++;
            // cout<<sum<<endl;
        }
        // for(int i=0;i<k;i++){
        //     cout<<c[i];
        // }
        // cout<<endl;
        int* dear = new int [k]; 
        for(int i = 1;i <= k; i++){
            dear[i-1]=c[k - i];
        }
        
        // for(int i=0;i<k;i++){
        //     cout<<dear[i];
        // }
        //  cout<<endl;
        int firstNonZeroIndex = 0;
        while (firstNonZeroIndex < k && dear[firstNonZeroIndex] == 0) {
            firstNonZeroIndex++;
        }
        // cout<<firstNonZeroIndex<<endl;
        // cout<<k<<endl;
        // int newIndex = 0;
        int* ans =new int [k-firstNonZeroIndex];
        for (int i = firstNonZeroIndex; i < k; i++) {
            ans[i-firstNonZeroIndex] = dear[i];
        }
        // for(int i=0;i<k-firstNonZeroIndex;i++){
        //     cout<<ans[i];
        // }
        // cout<<endl;

        UnlimitedInt* i3 = new UnlimitedInt(ans,k-firstNonZeroIndex, newSign, k-firstNonZeroIndex);
        return i3;
    }     

    return new UnlimitedInt("1");
 }

 ///// MY FINAL MULTIPLY
        
UnlimitedInt* single(UnlimitedInt* i1, int x, int s){
    int* a = i1->get_array();
    int n1 = i1->get_size();
    int* c = new int[n1+2];
    int i = n1-1; int k = 0;
    int carry = 0; int p = 0;
    while(i >= 0){
        p = carry;
        p += a[i]*x;
        carry = p / 10;
        i--;
        c[k] = p % 10;
        k++;
    }
    if(carry != 0){
        c[k] = carry;
        k++;
    }
        for(int i=0;i<k/2;i++){
            int temp = c[i];
            c[i] = c[k-i-1];
            c[k-i-1] = temp;
        }
        int firstNonZeroIndex = 0;
        while (firstNonZeroIndex < k && c[firstNonZeroIndex] == 0) {
            firstNonZeroIndex++;
        }
        int newIndex = 0;
        for (int i = firstNonZeroIndex; i < k; i++) {
            c[newIndex] = c[i];
            newIndex++;
        }
        k = newIndex;
        // delete a;
        UnlimitedInt* r = new UnlimitedInt(c,k,s,k);
        return r;
}

UnlimitedInt* ten(UnlimitedInt* b,int e){
    int* a = b->get_array();
    int n = b->get_size();
    int* r = new int[n+e];
    for(int i = 0; i < n;i++){
        r[i] = a[i];
    }
    for(int i = 0; i < e; i++){
        r[n+i] = 0;
    }
    // delete a;
    UnlimitedInt* ans = new UnlimitedInt(r,n+e,b->get_sign(),n+e);
    return ans;
}


UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {

        int sign = i1->get_sign() * i2->get_sign();
        int* b = i2->get_array();
        int n2 = i2->get_size();
        UnlimitedInt* x = single(i1,b[n2 - 1],sign);
        UnlimitedInt* ans = x;
        UnlimitedInt* r = nullptr;
        int j = n2 - 2;
        while(j >= 0){
            r = single(i1,b[j],sign);
            r = ten(r,n2 - j - 1);
            ans = add(ans,r);
            j--;
        }
        return ans;
}
        
UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {
    int newSign = i1->get_sign() * i2->get_sign();
    UnlimitedInt* t1 = new UnlimitedInt(i1->to_string());
    UnlimitedInt* t2 = new UnlimitedInt(i2->to_string());
    UnlimitedInt* one = new UnlimitedInt("1");
    // UnlimitedInt* minusone = new UnlimitedInt("-1");

    if (compare(t1, t2) == -1) {
        return new UnlimitedInt(0);
    } else if (compare(t1, t2) == 0) {
        return new UnlimitedInt(newSign);
    } else {
        string s = t1->to_string();
        string quotient_string = "";
        int k = t2->get_size() - 1;
        string str = s.substr(0, t2->get_size());

        while (k < t1->get_size()) {
            UnlimitedInt* counter = new UnlimitedInt(0);
            UnlimitedInt* current = new UnlimitedInt(str);

            for (int i = 0; i <= 10; i++) {
                if (compare(current, mul(t2, counter)) <= 0) {
                    if(compare(current, mul(t2, counter)) != 0){
                        counter = sub(counter, one);
                        // cout<<counter->to_string()<<endl;
                    }
                    quotient_string += counter->to_string();
                     
                    // cout<<quotient_string<<endl;
                    current = sub(current, mul(t2, counter));
                    // cout<<current->to_string()<<endl;
                    // cout<<current->to_string()<<endl;
                    break;
                } else {
                    counter = add(counter, one);
                }
            }

            delete counter;
            k++;
            str=current->to_string();
            if (k < t1->get_size()) {
                str = str + s[k];
            }
            int zeros=0;
            if(str[0]=='0'){
                for(std::string::size_type j = 0; j<str.length() ; j++){
                    if(str[j]=='0'){
                        zeros++;
                    }
                    else{
                        break;
                    }
                }
            }
            str=str.substr(zeros);
        }
        
        int zeros=0;
        if(quotient_string[0]=='0'){
            for(std::string::size_type i = 0; i<quotient_string.length(); i++){
                if(quotient_string[i]=='0'){
                    zeros++;
                }
                else{
                    break;
                }
            }
        }
        if(newSign == -1){
            quotient_string = "-" + quotient_string;
        }
        // cout<<zeros<<endl;
        string h="";
        for(std::string::size_type i = zeros; i<quotient_string.length(); i++){
            h=h+quotient_string[i];
        }
        return new UnlimitedInt(h);
    }

    return new UnlimitedInt(0);
}


UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* d=div(i1,i2);
    d=sub(i1,mul(i2,d));
    return d;
}


//     // Conversion Functions 
string UnlimitedInt::to_string(){
    std::string s = "";
    if(sign == -1){
        s += "-";
    }
    for(int i = 0; i < size; i++){
        s += std::to_string(unlimited_int[i]);
    }
    return s;
}
// int main(){
//     UnlimitedInt* p = new UnlimitedInt("2158654168546859484874");
//     UnlimitedInt* q = new UnlimitedInt("145484894984989");
//     // std::cout<<UnlimitedInt::add(p,q)->to_string()<<std::endl;
//     // std::cout<<UnlimitedInt::sub(p,q)->to_string()<<std::endl;
//     // std::cout<<UnlimitedInt::mul(p,q)->to_string()<<std::endl;
//     std::cout<<UnlimitedInt::div(p,q)->to_string()<<std::endl;
// return 0;
// }























































