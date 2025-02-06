/*
3. C++程序设计
2. 第2周
1. A+B Problem

注意：总时间限制: 1000ms 内存限制: 65536kB

描述
Calculate a + b

输入
Two integer a,,b (0 ≤ a,b ≤ 10)

输出
Output a + b

样例输入
1 2

样例输出
3

提示
Q: Where are the input and the output?

A: Your program shall always read input from stdin (Standard Input) and write output to stdout (Standard Output). For example, you can use 'scanf' in C or 'cin' in C++ to read from stdin, and use 'printf' in C or 'cout' in C++ to write to stdout.

You shall not output any extra data to standard output other than that required by the problem, otherwise you will get a "Wrong Answer".

User programs are not allowed to open and read from/write to files. You will get a "Runtime Error" or a "Wrong Answer" if you try to do so. 

Here is a sample solution for problem 1000 using C++/G++:
*/

#include <iostream>
using namespace std;
int main()
{
    int a,b;
    cin >> a >> b;
    cout << a+b << endl;
    return 0;
}