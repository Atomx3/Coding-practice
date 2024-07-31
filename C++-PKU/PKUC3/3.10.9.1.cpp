/*
3. C程序设计进阶
10. 第10周
9. 编程题＃9：人群的排序和分类

另一个版本的程序案例。

修改了main函数中
set<A*,Comp> ct;// 将A修改为存储Person指针
set<Person*,Comp> ct;

*/
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

// 定义基类Person存储共同属性（如类型和年龄）和方法（如打印功能）。
class Person {
public:
    char type;
    int age;
    Person(char c, int a) : type(c), age(a) {}
    virtual void print() const {
        cout << type << " " << age << endl;
    }
};

// A类继承自Person类，拥有Person类的所有属性和方法。
class A: public Person {
public: // 使用Person类的构造函数初始化类型为'A'和年龄。
    A(int a) : Person('A', a) {}
    // 重写print方法以输出'A'和年龄。
    // void print() const override {
    //     cout << "A " << age << endl;
    // }
};

// A类继承自Person类，同上
class B : public Person {
public:// 使用Person类的构造函数初始化类型为'B'和年龄。
    B(int a) : Person('B', a) {}
    // 重写print方法以输出'B'和年龄。
    // void print() const override {
    //     cout << "B " << age << endl;
    // }
};

// 比较类Comp，用于排序
class Comp {
public:
    bool operator() (const Person* lhs, const Person* rhs) const {
        return lhs->age < rhs->age;
    }
};

// 打印函数Print，用于输出
void Print(Person* p) {
    p->print();
}


int main()
{
        int t;
        cin >> t;
        set<Person*,Comp> ct;// 将A修改为存储Person指针
        while( t -- ) {
                int n;
                cin >> n;
                ct.clear();
                for( int i = 0;i < n; ++i)	{
                        char c; int k;
                        cin >> c >> k;

                        if( c == 'A')
                                ct.insert(new A(k));
                        else
                                ct.insert(new B(k));
                }
                for_each(ct.begin(),ct.end(),Print);
                cout << "****" << endl;
        }
}