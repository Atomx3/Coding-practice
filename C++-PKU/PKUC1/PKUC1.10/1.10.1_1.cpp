/*
1. 计算导论与C语言基础，系列第1课  
10. 理性认识C程序 导论，第10周  
1. 编程题＃1：求字母的个数
another solution to the subject 1.


1. You should use a single string variable instead of an array of string.
2. The getline function should be used correctly to read the entire line.
3. The loop to count the vowels should iterate over the characters of the string.

*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    // Input the string
    string s;
    getline(cin, s);

    // Count letters a, e, i, o, u in the string
    int countsA = 0, countsE = 0, countsI = 0, countsO = 0, countsU = 0;
    for (char c : s) {
        if (c == 'a') { countsA++; }
        else if (c == 'e') { countsE++; }
        else if (c == 'i') { countsI++; }
        else if (c == 'o') { countsO++; }
        else if (c == 'u') { countsU++; }
    }

    // Output the counts
    cout << countsA << " " << countsE << " " << countsI << " " << countsO << " " << countsU << endl;

    return 0;
}
