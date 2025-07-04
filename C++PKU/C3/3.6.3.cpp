/*
3. C++程序设计
6. 第6 module
3. 编程题＃3：

polymorphism
virtual function

1. void Call(A* p)  {
    p->Fun();  p->Do();
}
1.1. p->Do() dereferences the pointer p first 
and then calls the member function Do() 
on the object pointed to by p.

1.2. p->Do() is equivalent to: (*p).Do()
It combines the * dereference operator 
with the . member access operator.

2. Call( new C() );
2.1. p->Fun() calls the Fun() method on the C object. 
Since C inherits from B and A, 
and Fun() is not overridden in C, 
prints "A::Fun".

2.2. p->Do() calls the Do() method.
C's overridden Do() is called,
demonstrating polymorphism in action.
prints "C::Do".

*/

#include <iostream>
using namespace std;
class A {
    private:
        int nVal;
    public:
        void Fun()
        { cout << "A::Fun" << endl; }
        virtual void Do()
        { cout << "A::Do" << endl; }
};
class B:public A {
    public:
        void Do()
        { cout << "B::Do" << endl; }
};
class C:public B {
    public:
        void Do( )
        { cout << "C::Do" << endl; }
        void Fun()
        { cout << "C::Fun" << endl; }
};
void Call(A* p)  {
    p->Fun();  p->Do();
}
int main()  {
    Call( new A() );
    Call( new C() );
    return 0;
}