/*
1. 计算导论与C语言基础，系列第1课  
8. 理性认识C程序 导论，第8周  
2.4 编程题＃4：找和为K的两个元素

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个长度为n(n < 1000)的整数序列中，判断是否存在某两个元素之和为k。

输入
第一行输入序列的长度n和k，用空格分开。

第二行输入序列中的n个整数，用空格分开。

输出
如果存在某两个元素的和为k，则输出yes，否则输出no。

样例输入
9 10
1 2 3 4 5 6 7 8 9

样例输出
yes


*/

#include<iostream>
using namespace std;

int main()
{
// input n, k, and array a[n].
int n=0, k=0;
bool findK=false;
cin>>n>>k;

int a[n];
for(int i=0; i<n; i++){
    cin>>a[i];
}

// find out if there are two integers in the array a[] that the sum equal to k. 
for(int i=0; i<n; i++){
    for(int j=i+1; j<=n; j++){
        if(a[i]+a[j]==k){
        findK=true;
        break;
    }
    }    
}

if(findK==false)
    cout<<"no"<<endl;
else
    cout<<"yes"<<endl;

	return 0;
}