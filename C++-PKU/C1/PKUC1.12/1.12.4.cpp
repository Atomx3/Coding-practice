#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

/*
编程题＃4：简单计算器

*/

int main()
{
// input a, b, and operator symbol oprt
int a=0, b=0;
char oprt=' ';
while(cin>>a>>b>>oprt){

switch(oprt){
    case '+':
    cout<<a+b<<endl;
    break;
    case '-':
    cout<<a-b<<endl;
    break;
    case '*':
    cout<<a*b<<endl;
    break;
    case '/':
       if(b==0){
        cout<<"Divided by zero!"<<endl;
        }
        else cout<<a/b<<endl;
    
    break;
    default:
    cout<<"Invalid operator!"<<endl;
    break;

    }
}


    return 0;   
}


/*
example data

intput
1 2 +
1 0 /
1 0 XOR

output 
3
Divided by zero!
Invalid operator!

*/