/*
3. C程序设计进阶
10. 第10周
2. 编程题＃2：

"Number(int n)" declares the constructor 
with a single parameter n of type int.

": num(n) " is an initializer list that
directly initializes the num member variable 
with the value passed to n.

input
output：
2
2
8
10

*/

#include <iostream>
using namespace std;

class Number {
public:
    int num;
    // : num(n) is an initializer list
    Number(int n): num(n) {
    }
    // Function to get the value of num
    // member function that returns a reference to num
    int& value(){
        return num;
    }
    // Overload the + operator to add two Numbers
    Number operator+(const Number& rhs) {
        this->num += rhs.num;
        return *this;
    }
};

int main() {
    Number a(2);
    Number b = a;
    cout << a.value() << endl;
    cout << b.value() << endl;
    a.value() = 8;
    cout << a.value() << endl;
    a+b;
    cout << a.value() << endl;
    return 0;
}