/*
2. C程序设计进阶
3. 第三周
3. 编程题＃2：角谷猜想
Collatz conjecture.
*/

#include <iostream>
using namespace std;

int Collatz(int n)
{
    if (n > 1){
        if (n % 2 == 0){
            cout<< n<< "/2=";
            n = n / 2;
            cout<< n <<endl;
        }
        else{
            cout<< n <<"*3+1=";
            n = n * 3 + 1;
            cout<< n <<endl;
        }
        return Collatz(n);
    }
    else if(n == 1) {
        cout<< "End" <<endl; // "END" will output wrong answer.
        return 0;
    }
    return 0;
}

int main()
{
    int n;
    while(cin>> n){
        if(n<1) break;
        Collatz(n);
    }
    return 0;
}