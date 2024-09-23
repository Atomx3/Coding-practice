/*
1. 计算导论与C语言基础，系列第1课  
7. 理性认识C程序 导论，第7周  
1.2 抄写题＃2：分数求和

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
输入n个分数并对他们求和，用约分之后的最简形式表示。 

比如： 

q/p = x1/y1  + x2/y2 +....+ xn/yn.

q/p要求是归约之后的形式。 

如：5/6已经是最简形式，3/6需要规约为1/2, 3/1需要规约成3，10/3就是最简形式。 

PS:分子和分母都没有为0的情况，也没有出现负数的情况

输入
第一行的输入n, 代表一共有几个分数需要求和

接下来的n行是分数

输出
输出只有一行，即归约后的结果

样例输入
2
1/2
1/3

样例输出
5/6

*/

#include <iostream>
using namespace std;

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}

int main() {
    // Number of fractions
    int n = 0;
    cin >> n;

    // Arrays to store numerators and denominators
    int x[n], y[n];
    for (int i = 0; i < n; i++) {
        string fraction;
        cin >> fraction;
        // if find "/", calculate as normal Fraction.
        size_t pos = fraction.find("/");
        if (pos != string::npos) {
            x[i] = stoi(fraction.substr(0, pos));
            y[i] = stoi(fraction.substr(pos + 1));
        } else { // else not find "/", set Denominator as 1 
            x[i] = stoi(fraction);
            y[i] = 1;
        }
    }

    // Calculate the sum of the fractions
    int sumx = x[0], sumy = y[0];
    for (int i = 1; i < n; i++) {
        sumx = sumx * y[i] + x[i] * sumy;
        sumy *= y[i];
    }

    // Reduce the fraction to its simplest form
    int g = gcd(sumx, sumy);
    sumx /= g;
    sumy /= g;

    // Output the result
    if (sumy == 1) {
        cout << sumx << endl;
    } else {
        cout << sumx << "/" << sumy << endl;
    }

    return 0;
}
