/*
3. C程序设计进阶
6. 第6周
3. 编程题＃3：
polymorphism
virtual function
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