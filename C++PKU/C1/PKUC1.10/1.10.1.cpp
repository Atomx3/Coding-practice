/*
1. 计算导论与C语言基础，系列第1课  
10. 理性认识C程序 导论，第10 module  
1. 编程题＃1：求字母的个数

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个字符串中找出元音字母a,e,i,o,u出现的次数。

输入
输入一行字符串（字符串中可能有空格，请用cin.getline(s,counts)方法把一行字符串输入到字符数组s中，其中counts是s的最大长度，这道题里面可以直接写80。），字符串长度小于80个字符。

输出
输出一行，依次输出a,e,i,o,u在输入字符串中出现的次数，整数之间用空格分隔。

样例输入
If so, you already have a Google Account. You can sign in on the right.

样例输出
5 4 3 7 3
提示
注意，只统计小写元音字母a,e,i,o,u出现的次数。

*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int counts = 80;
    char s[counts];
    
    // Initialize the array with zeros
    for (int i = 0; i < counts; i++) {
        s[i] = '\0';
    }

    cin.getline(s, counts);

    // count letters a, e, i, o, u in the string array s.
    int i = 0, countsA = 0, countsE = 0, countsI = 0, countsO = 0, countsU = 0;
    while (s[i] != '\0') {
        if (s[i] == 'a') { countsA++; }
        else if (s[i] == 'e') { countsE++; }
        else if (s[i] == 'i') { countsI++; }
        else if (s[i] == 'o') { countsO++; }
        else if (s[i] == 'u') { countsU++; }
        i++;
    }

    cout << countsA << " " << countsE << " " << countsI << " " << countsO << " " << countsU << endl;

    return 0;
}
