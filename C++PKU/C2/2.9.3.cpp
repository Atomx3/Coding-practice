/*
2. C程序设计进阶
9. 第9 module
3. 编程题＃3：运算符判定

Attention: 
in many cases, the answer more than one.
such as 5%3=2, 5-3=2; 
so, the conditional expression would be all changed as "if", 
but not "else if" since the second expression.
*/
#include <iostream>
using namespace std;

void sign(int a, int b, int c){
    bool conditionMet = false;
    if(a+b==c){
        cout<<"+"<<endl;
        conditionMet = true;
    }
    else if(a-b==c){
        cout<<"-"<<endl;
        conditionMet = true;
    }
    else if(a/b==c){
        cout<<"/"<<endl;
        conditionMet = true;
    }
    else if(a*b==c){
        cout<<"*"<<endl;
        conditionMet = true;
    }
    else if(a%b==c){
        cout<<"%"<<endl;
        conditionMet = true;
    }
    else if(!conditionMet){
        cout<<"error"<<endl;
    }
}

int main(){
    int a=0, b=0, c=0;
    char comma;// To ignore the comma
    cin>>a>>comma>>b>>comma>>c;
    //cout<<a<<" "<<b<<" "<<c<<endl;

    sign(a,b,c);
    return 0;

}