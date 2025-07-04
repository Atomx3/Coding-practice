/*
3. C程序设计进阶
10. 第10 module
1. 编程题＃1：输出200


n1 is implicitly passed to the operator function.
n1 is the object the function is called on. 
n1 corresponds to the this pointer that points to the current object.
“this” is the implicit pointer to the object that called the function.

It does not get “passed” to the function in the traditional sense of argument passing. 
n1 is the context in which the function operates. 
Inside the function, the member variable num of n1 
can be accessed with this->num or simply num 


n2 is explicitly passed as an argument to the function. 
n2 corresponds to the parameter rhs (right-hand side).

n1 是调用*运算符函数的对象 n1 = num (accessed via this->num), n1比较特殊，其值并非传递至num
n2 作为参数传入*函数， n2 = rhs.num

n1 (Number object)
  |
  |  .operator*(n2)
  | /
  |/
  *  (Overloaded Operator Function)
 /|
/ |
  |
n2 (Number object)

input: 
output: 200
*/


#include<iostream>
using namespace std;

class Number {
public:
    int num;
    Number(int n=0): num(n) {}
    // Overload the * operator to multiply two Number objects.
    Number operator*(const Number& rhs) const {
        return Number(num * rhs.num);
    }
    // Overload the int() operator to convert Number to int.
    operator int() const {
        return num;
    }
};

int main() {
    Number n1(10), n2(20);
    Number n3; n3 = n1*n2; // function call n1*n2 = n1.operator*(n2);
    cout << int(n3) << endl;
    return 0;
}