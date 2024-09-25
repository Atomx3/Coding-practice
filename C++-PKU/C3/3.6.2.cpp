/*
3. C++程序设计
6. 第6周
2. 编程题＃2：
polymorphism
virtual function
virtual destructor
*/

#include <iostream>
using namespace std;
class A {
    public:
        virtual ~A() { cout << "destructor A" << endl; }
};
class B:public A {
    public:
        ~B() { cout << "destructor B" << endl; }
};
int main() {
    A * pa;
    pa = new B;
    delete pa;
    return 0;
}