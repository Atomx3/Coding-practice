/*
3. C程序设计进阶
10. 第10 module
10. 编程题＃10：输出指定结果二

*/

#include <iostream>
#include <map>
using namespace std;

class A {
public:
    static int count;
    int age;
    A(int a) : age(a) { count++; }
    A() : age(0) { count++; }
    A(const A& other) : age(other.age) { /* 复制构造函数不增加count */ }
    virtual ~A() {
        cout << "A::destructor" << endl;
        count--;
    }
};

class B : public A {
public:
    B(int a) : A(a) {}
    B(const B& other) : A(other) { /* 复制构造函数不增加count */ }
    ~B() override {
        cout << "B::destructor" << endl;
        // 不需要修改count，因为A的析构函数会被调用
    }
};
// 该变量是用来记录一共有多少个类A及类A的派生类的对象的。
int A::count = 0;

void func(B& b) {
    B* temp = new B(b.age); // 创建一个新的B类对象
    delete temp; // 删除对象，触发析构函数
}

int main() {
    A a1(5), a2; // count is 2
    cout << A::count << endl; // 输出2
    B b1(4); // count is 3
    cout << A::count << endl; // 输出3
    func(b1); // 创建新对象，然后删除，count是3
    cout << A::count << endl; // 输出3
    A* pa = new B(4); // count is 4
    cout << A::count << endl; // 输出4
    delete pa; // count is 3
    cout << A::count << endl; // 输出3
    return 0;
}
