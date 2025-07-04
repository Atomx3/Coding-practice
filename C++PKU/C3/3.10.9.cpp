/*
3. C程序设计进阶
10. 第10 module
9. 编程题＃9：人群的排序和分类

输入
第一行是整数t,表明一共t组数据. t < 20

对每组数据：
第一行是整数n,表示下面一共有n行。 0 < n < 100。
下面的每行代表一个人。每行以一个字母开头，代表该人所属的类别，然后跟着一个整数，代表年龄。
字母只会是 'A‘或‘B'，整数范围0到100，数据保证年龄都不相同。
4
A 3
B 4
A 5
B 6


输出
对每组输入数据，将这些人按年龄从小到大输出。
每个人先输出类别，再输出年龄。每组数据的末尾加一行 "****"
A 3
B 4
A 5
B 6
****

*/
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>
using namespace std;

// 定义一个基类Person来存储共同属性和方法
// class Person {
// public:
//     char type;
//     int age;
//     Person(char c, int a) : type(c), age(a) {}
//     virtual void print() const {
//         cout << type << " " << age << endl;
//     }
// };

// 定义一个基类存储共同属性和方法
class A {
public:
    int age;
    A(int a) : age(a) {}
    virtual void print() const {
        cout << "A " << age << endl;
    }
};

// B类继承自A
class B : public A {
public:
    B(int a) : A(a) {}
    void print() const override {
        cout << "B " << age << endl;
    }
};

// 比较类Comp，用于排序
class Comp {
public:
    bool operator() (const A* lhs, const A* rhs) const {
        return lhs->age < rhs->age;
    }
};

// 打印函数Print，用于输出
void Print(A* a) {
    a->print();
}


int main()
{

        int t;
        cin >> t;
        set<A*,Comp> ct;
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