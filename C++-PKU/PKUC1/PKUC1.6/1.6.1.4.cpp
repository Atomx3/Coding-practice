/*
1. 计算导论与C语言基础，系列第1课  
6. 理性认识C程序 导论，第6周  
1.4 编程题＃4：最大奇数与最小偶数之差的绝对值

描述
输入6个正整数，且这6个正整数中至少存在一个奇数和一个偶数。 

设这6个正整数中最大的奇数为a，最小的偶数为b，求出|a-b|的值

输入
输入为一行，6个正整数,且6个正整数都小于100

输入保证这6个数中至少存在一个奇数和一个偶数

输出
输出为一行，输出最大的奇数与最小的偶数之差的绝对值

样例输入
第一组
1 2 3 4 5 6
第二组
1 6 3 8 5 10

样例输出
第一组
3
第二组
1

how to compile the program, eg.
g++ -std=c++11 -o program 1.6.1.3.cpp
*/

#include <iostream>
using namespace std;

int main() {

    // input n values, store in array t[n]
    int t[6];
    for(int i=0; i<6; i++){
        cin>>t[i]; 
    }

    // find the even number,store in even[j];
    int even[6], j=0;
    for(int i=0; i<6; i++){
        if(t[i]%2 == 0){
                even[j]= t[i];
                j++;
            }  
        }
    // find the min even=b in even[j];
    int b=even[0];
    for(int i=1; i<j; i++){
        if(even[i]<b){
            b= even[i];
        }
    }

    // output;
    // cout<< b <<endl;

// find the odd number,store in odd[k];
    int odd[6], k=0;
    for(int i=0; i<6; i++){
        if(t[i]%2 == 1){
            odd[k]= t[i];
            k++;
        }  
    }
    // find the max odd=a in odd[k];
    int a=odd[0];
    for(int i=1; i<k; i++){
        if(odd[i]>a){
            a= odd[i];
        }
    }

    // output;
    // cout<< a <<endl;

    // get the absolute value of a-b
    cout<<abs(a-b)<<endl;

    return 0;
    }
    

   