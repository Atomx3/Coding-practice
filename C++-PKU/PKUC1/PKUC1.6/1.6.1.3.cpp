/*
1. 计算导论与C语言基础，系列第1课  
6. 理性认识C程序 导论，第6周  
1.3 编程题＃3：最高的分数

描述
孙老师讲授的《计算概论》这门课期中考试刚刚结束，他想知道考试中取得的最高分数。
因为人数比较多，他觉得这件事情交给计算机来做比较方便。你能帮孙老师解决这个问题吗？

输入
输入两行，第一行为整数n（1 <= n < 100），表示参加这次考试的人数.
第二行是这n个学生的成绩，相邻两个数之间用单个空格隔开。
所有成绩均为0到100之间的整数。

输出
输出一个整数，即最高的成绩。

样例输入
5
85 78 90 99 60

样例输出
99

*/

#include <iostream>
using namespace std;


int main() {
    // input n>=1, n<100. 
    int n=1, Max=0;
    do{
        cin>>n;
        if (n < 1 || n > 99) {
            cout << "invalid value，please input again" << endl;
        }

    }while (n < 1 || n > 99);
    
   
    // solution 1: input array t[n] with value [0, 100]
    // int t[n];
    // for(int i=0; i<n; i++){
    //     do{
    //         cin>>t[i]; 
    //         if (t[i] < 0 || t[i] > 100){
    //             cout << "invalid value，please input again" << endl;
    //         }
    //     }while (t[i] < 0 || t[i] > 100); 
    // }
    // // find the Max value in t[i];
    // for(int i=0; i<n; i++){
    //     if(t[i]>=0 && t[i]<=100 && t[i]>Max){
    //         Max= t[i];
    //     }
    // }

    // solution 2: input scores and find the Max value directly.
    int score=1;
    for(int i=0; i<n; i++){
        cin>>score; 
        // while loop is simpler than do while.
        while (score < 1 || score > 99){
        cout << "invalid value，please input again" << endl;
        cin >> score;
        }

        if(score>Max){
            Max= score;
        }
    }
   
 
    // output;
    cout<<Max<<endl;

    return 0;
}
