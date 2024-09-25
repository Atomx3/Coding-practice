/*
3. C程序设计进阶
10. 第10周
10. 编程题＃10：输出指定结果二

本案例失败，等待修复

*/

#include <iostream>
#include <map>
using namespace std;

class B;

class A {
public:
    static int count;
    int age;
    A(int a) : age(a) { count++; }
    A() : age(0) { count++; }
    A(const A& other) : age(other.age) {} // 复制构造函数不增加count
    virtual ~A() {
        cout << "A::destructor" << endl;
        count--;
    }
};

class B : public A {
public:
    B(int a) : A(a) {}
    B(const B& other) : A(other) {} // 复制构造函数不增加count
    ~B() override {
        cout << "B::destructor" << endl;
    }
};

int A::count = 0;


void func(B b) {
    // Add functionality to manipulate the B object here
    //cout << "B object with age: " << b.age << endl; // Uncomment this line to print B object's age
}

int main() {
    A a1(5), a2;
    //cout << A::count << endl; // This line is commented out

    B b1(4);
    cout << A::count << endl; // Output: 2

    func(b1);
    cout << A::count << endl; // Output: 3

    A* pa = new B(4);
    cout << A::count << endl; // Output: 3

    delete pa;
    cout << A::count << endl; // Output: 2

    return 0;
}
