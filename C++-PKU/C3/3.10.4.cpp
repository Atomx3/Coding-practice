/*
3. C程序设计进阶
10. 第10周
4. 编程题＃4：计算整数平方和

下列程序每次读入一个整数N，若N为0则退出，否则输出N和N的平方。

输入:
K个整数。除最后一个数据外，其他数据均不为0。
1 5 8 9 0

输出:
K-1行。第I行输出第I个输入数和它的平方。
1 1
5 25
8 64
9 81

*/

#include <iostream>
using namespace std;

class CType {
private:
    int value;
public:
    // 构造函数
    CType() : value(0) {}

    // 设置值的函数
    void setvalue(int n) {
        value = n;
    }

    // 重载前置++运算符
    CType& operator++() {
        // Increment the current object's value
        value *= value; // 将值设置为其平方
        return *this;
    }

    // 重载后置++运算符
    // holds the current state of obj before ++.
    CType operator++(int) {
        CType temp = *this;
        ++(*this); // 调用前置++来平方值 value = value * value;
        return temp; // 返回原始值
    }

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const CType& obj) {
        os << obj.value;
        return os;
    }
};

int main(int argc, char* argv[]) {
        CType obj;
        int n;
        cin>>n;
        while ( n ) {
                obj.setvalue(n);
                cout<<obj++<<" "<<obj<<endl;
                cin>>n;
        }
        return 0;
}