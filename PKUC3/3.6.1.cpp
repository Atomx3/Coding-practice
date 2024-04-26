/*
3. C程序设计进阶
6. 第6周
1. 编程题＃1：
polymorphism
virtual function

A::Do() is non-virtual originally.

B derives from A and declares Do() as virtual, overriding A::Do().

This makes A::Do() implicitly virtual retroactively.

C derives from B, and overrides B::Do() with C::Do().

Since A::Do() is now virtual, C::Do() can override it as well.

*/

#include <iostream>
using namespace std;

class A {
    private:
        int nVal;
    public:
        void Fun()
        { cout << "A::Fun" << endl; }
        void Do() 
        { cout << "A::Do" << endl; }
};
class B:public A { //derived from class A and has a virtual function Do()
    public:
        virtual void Do() // overridden in derived classes B.
        { cout << "B::Do" << endl; }
};
class C:public B {
    public:
    void Do()
    { cout << "C::Do" <<endl; }
    void Fun()
    { cout << "C::Fun" << endl; }
};
void Call(B& p)  {
    p.Fun();  p.Do();
}
int main()  {
    C c;    Call(c);
    return 0;
}