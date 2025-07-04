/*
1. 计算导论与C语言基础，系列第1课  
6. 理性认识C程序 导论，第6 module  
1.1 编程题＃1：苹果和虫子  

描述  
你买了一箱n个苹果，很不幸的是买完时箱子里混进了一条虫子。虫子每x小时能吃掉一个苹果，假设虫子在吃完一个苹果之前不会吃另一个，那么经过y小时你还有多少个完整的苹果？

- 输入
输入仅一行，包括n，x和y（均为整数）。

- 输出
输出也仅一行，剩下的苹果个数

- 样例输入
第一组
10 4 9
第二组
10 4 36
第三组
10 4 100

- 样例输出
第一组
7
第二组
1
第三组
0

*/

#include <iostream>
using namespace std;

int main() {
    // input 
    int n, x, y, left;
    cin >> n>> x>> y;
    left = n- y/x;

    // output.
    if(y%x!=0 && left>=1){    
        cout<< left -1 <<endl;
    }
    else if(left<0) {cout<< 0 <<endl;}
    else {cout<< left <<endl;}



    return 0;
}
