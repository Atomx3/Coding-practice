/*
1. 计算导论与C语言基础，系列第1课  
8. 理性认识C程序 导论，第8 module  
2.1 编程题＃1：数字求和

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
给定一个正整数a，以及另外的5个正整数，问题是：这5个整数中，小于a的整数的和是多少？

输入
输入一行，只包括6个小于100的正整数，其中第一个正整数就是a。

输出
输出一行，给出一个正整数，是5个数中小于a的数的和。

样例输入
10 1 2 3 4 11

样例输出
10


*/

#include<iostream>
using namespace std;

int main(){
int n[6], i;
for(i=0; i<6; i++)
cin>> n[i];

int sum=0;
for(i=0; i<6; i++){
    if(n[i]<n[0]){sum+=n[i];}
}

cout<<sum<<endl;    
    
    return 0;
}
