/*
1. 计算导论与C语言基础，系列第1课  
7. 理性认识C程序 导论，第7周  
2.2 编程题＃2：成绩判断

描述
输入一个0--100的分数，判断分数代表什么等级。

95<=分数<=100, 输出1

90<=分数<95,输出2

85<=分数<90,输出3

80<=分数<85,输出4

70<=分数<80,输出5

60<=分数<70输出6

分数 < 60;输出7.

输入
n

输出
m

样例输入 87
样例输出 3

*/

#include <iostream>
using namespace std;

int main() {

// input n
int n=0;
cin>>n;

if(95<=n && n<=100)
cout<< 1 <<endl;
else if(90<=n && n<95)
cout<< "2" <<endl;
else if(85<=n && n<90)
cout<< 3 <<endl;
else if(80<=n && n<85)
cout<< 4 <<endl;
else if(70<=n && n<80)
cout<< 5 <<endl;
else if(60<=n && n<70)
cout<< 6 <<endl;
else if (n>=0 & n<60)
cout<< 7 <<endl;
else
cout<< "please input right number shold be  0 <= n <= 100" <<endl;

    return 0;
    }
    

   