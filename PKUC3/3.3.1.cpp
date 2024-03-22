/*
3. C程序设计进阶
3. 第3周
1. 编程题＃1：
*/
#include <iostream>
using namespace std;

class A {
public:
    int val;
    A(int n = 0){
        val = n;
    }
    ~A(){}
    // declares a member function GetObj()
    // returns a reference to an object of type A.
    A& GetObj(){
        // return value is this pointer = reference to A.
        return *this;
    }
};
int main()  {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
    return 0;
}