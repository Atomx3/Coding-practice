/*
3. C程序设计进阶
4. 第4周
1. 编程题＃1：

input

output
3+4i
5+6i
*/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Complex {
private:
    double r,i;
public:
    void Print() {
        cout << r << "+" << i << "i" << endl;
    }
// 重载=操作符，实现从字符串到Complex的隐式转换
    Complex& operator=(string s) {
        this->set(s);
        return *this;
    }
// 请补足Complex类的成员函数，不可增加成员变量。
    void set(string s) {
        char* str = new char[s.length()+1];
        strcpy(str, s.c_str());

        char* real = strtok(str, "+");
        this->r = atof(real);

        char* imag = strtok(NULL, "i");
        this->i = atof(imag);

        delete[] str;
    }

};
int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}