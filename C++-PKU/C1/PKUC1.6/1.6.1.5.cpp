/*
1. 计算导论与C语言基础，系列第1课  
6. 理性认识C程序 导论，第6周  
1.5 编程题＃5：分离整数的各个数位

描述
从键盘输入一个任意的三位整数，要求正确地分离出它的百位、十位和个位数，并分别在屏幕上输出，输出采用每行输出一个数的方式，不带其它符号。

输入
一个任意的三位整数

输出
一个任意的三位整数

样例输入
123

样例输出
1
2
3
*/

#include <iostream>
using namespace std;

int main() {
    // input n values;
    int n;
    cin>>n;

    // seperate decimal;
    int x, y, z;
    x= n/100;
    y= (n%100)/10;
    z= (n%100)%10;

    // output;
    cout<< x <<endl;
    cout<< y <<endl;
    cout<< z <<endl;
    

    return 0;
}
