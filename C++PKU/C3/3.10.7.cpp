/*
3. C程序设计进阶
10. 第10 module
7. 编程题＃7：字符串排序

MyLarge<A>() 创建的是一个临时的比较器对象，
它提供了比较两个 A 类型对象所需的逻辑，但不包含任何数据。
实际参与排序的数据是 lst 中已经存在的 A 类型对象。

*/

#include <iostream>
#include <string>
#include <list>
using namespace std;

class A{
private:
        string name;
public:
        A(string n) :name(n){} // consructor of class A
        // 友元函数可访问 A 类的私有成员name，函数体通常在类定义外部实现
        friend bool operator < (const class A& a1, const class A &a2);
        // 友元函数，在类内部提供一个内联的函数体
        friend bool operator == (const class A &a1, const class A &a2){
                if (a1.name.size() == a2.name.size())
                        return true;
                else
                        return false;
        }
        friend ostream & operator << (ostream &o, const A &a){
                o << a.name;
                return o;
        } // 声明定义 get_name(), get_size()函数
        string get_name() const{ 
                return name;
        }
        int get_size() const{ // size() 是STL（标准模板库）中的内置函数
                return name.size();
        }
};

// 按照字符串首字符ASCII码序从小到大排序
bool operator < (const A& a1, const A& a2) {
    return a1.get_size() < a2.get_size();
}

// 模板类MyLarge ，按照字符串长度从小到大排序
// main(){ MyLarge<A>()}特定于 A 类型的 MyLarge 实例
template<class T>
class MyLarge { 
public: // MyLarge<A>()调用 MyLarge 类的默认构造函数
    bool operator()(const T& a1, const T& a2) {
        return a1.get_name()[0] < a2.get_name()[0];
    }
};

// 定义 Print 类
class Print {
public:
    void operator()(const A& a) {
        cout << a << " ";
    }
};

void Show(list<A>::iterator begin, list<A>::iterator end, Print print) {
    for (auto it = begin; it != end; ++it) {
        print(*it); // 使用 Print 类的实例来打印每个元素
    }
}

int main(int argc, char* argv[])
{       // 创建序列容器对象lst
        list<A> lst;
        int ncase, n, i = 1;
        string s;
        cin >> ncase;
        while (ncase--){
                cout << "Case: "<<i++ << endl;
                cin >> n;
                for (int i = 0; i < n; i++){
                         cin >> s;
            // 通过list成员函数push_back，在列表的末尾添加新元素
            // 新元素为A类的对象s，即字符串 s 作为参数传入列表
                         lst.push_back(A(s));
                }
                // sort 函数将使用 A 类型的 < 操作符重载来比较元素。
                // 按照字符串长度从小到大排序
                lst.sort();
                Show(lst.begin(), lst.end(), Print());
                cout << endl; 
                // MyLarge类操作的数据类型为<A>
                // 按照字符串首字符ASCII码序从小到大排序
                lst.sort(MyLarge<A>());// MyLarge临时实例操作lst列表中的参数
                Show(lst.begin(), lst.end(), Print());
                cout << endl;
                lst.clear();
        }
        return 0;
}