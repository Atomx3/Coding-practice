/*
3. C程序设计进阶
3. 第3周
3. 编程题＃3：
*/
#include <iostream>
using namespace std;

class Base {
public:
    int k;
    Base(int n):k(n) { }
    ~Base(){}
};

class Big  {
public:
    int v; Base b;
    // member initialization list
    Big(int value) : v(value), b(value){}
    ~Big(){}
};
int main()  {
    Big a1(5);    Big a2 = a1;
    cout << a1.v << "," << a1.b.k << endl;
    cout << a2.v << "," << a2.b.k << endl;
    return 0;
}
