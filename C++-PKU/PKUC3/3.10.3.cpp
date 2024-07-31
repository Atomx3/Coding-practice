/*
3. C程序设计进阶
10. 第10周
3. 编程题＃3：计算数列平方和

请写出sum函数，使其可以计算输入数列的平方和。

int (*func)(int) 是一个函数指针的声明，
它指向一个接受一个 int 类型参数并返回一个 int 类型结果的函数。

input:
2
2
4 3
3
0 1 2

output：
25
5

*/

#include <iostream>
using namespace std;

// 在此处补充你的代码
int sqr(int n) {
    return n * n;
}

// sum函数，计算数列的平方和
// 名为 func 的函数指针接收 sqr 函数
int sum(int a[], int n, int (*func)(int)){
    int total = 0;
    for (int i=0; i<n; ++i){
        total += func(a[i]);// 使用传入的函数计算平方，并累加到总和中
    }
    return total;
}

int main() {
    int t, n, a[0x100];
    cin >> t;
    for (int c = 0; c < t; ++c) {
        cin >> n;
        for (int i = 0; i < n; ++i) cin >> a[i];
        cout << sum(a, n, sqr) << endl;// 调用sum函数并输出结果
    }
    return 0;
}