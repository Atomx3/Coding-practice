/* 递归 — 棋盘分割
将一个 8x8 的棋盘分割成 n 块矩形棋盘，每次切割都沿着棋盘格子的边进行，
使得这些矩形棋盘的总分的均方差最小。
这里的“总分”是指每块矩形棋盘内所有格子分值的总和。
为了解决这个问题，代码使用了动态规划的方法。
动态规划是一种算法设计技术，用于解决具有重叠子问题和最优子结构特性的问题。
在这个问题中，动态规划用于找到最优的切割方法，以最小化所有矩形棋盘总分的均方差。

每个棋盘格子的分值是通过输入数据定义的。

输入
第1行为一个整数n (1 < n < 15)
代表要分割成的矩形棋盘的数量。
第2行至第9行每行为8个小于100的非负整数, 
表示棋盘上相应格子的分值
每行相邻两数之间用一个空格分隔

样例输入
3
1 1 1 1 1 1 1 3
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 1
1 1 1 1 1 1 1 0
1 1 1 1 1 1 0 3

输出
仅一个数, 为均方差σ (四舍五入精确到小数点后三位）
样例输出
1.633
*/

#include <iostream>
#include <cstring>
#include <cmath>
#include <iomanip>
using namespace std;

int s[9][9]; // 每个格子的分数
int sum[9][9]; // (1,1)到(i,j)的矩形的分数之和
int res[15][9][9][9][9]; // fun的记录表

// 计算(x1,y1)到(x2,y2)的矩形的分数之和
int calSum(int x1, int y1, int x2, int y2) {
    return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
}

// 动态规划函数
int fun(int n, int x1, int y1, int x2, int y2) {
    if (res[n][x1][y1][x2][y2] != -1)
        return res[n][x1][y1][x2][y2];
    if (n == 1) {
        int t = calSum(x1, y1, x2, y2);
        res[n][x1][y1][x2][y2] = t * t;
        return t * t;
    }

    int MIN = 10000000;
    for (int a = x1; a < x2; a++) {
        int c = calSum(a + 1, y1, x2, y2);
        int e = calSum(x1, y1, a, y2);
        int t = min(fun(n - 1, x1, y1, a, y2) + c * c, fun(n - 1, a + 1, y1, x2, y2) + e * e);
        MIN = min(MIN, t);
    }
    for (int b = y1; b < y2; b++) {
        int c = calSum(x1, b + 1, x2, y2);
        int e = calSum(x1, y1, x2, b);
        int t = min(fun(n - 1, x1, y1, x2, b) + c * c, fun(n - 1, x1, b + 1, x2, y2) + e * e);
        MIN = min(MIN, t);
    }
    res[n][x1][y1][x2][y2] = MIN;
    return MIN;
}

int main() {
    memset(sum, 0, sizeof(sum));
    memset(res, -1, sizeof(res)); // 初始化记录表
    int n;
    cin >> n;
    // 读取每个格子的分值
    for (int i = 1; i < 9; i++) {
        for (int j = 1, rowsum = 0; j < 9; j++) {
            cin >> s[i][j];
            rowsum += s[i][j];
            // 矩形区域内所有格子分值的累加和
            sum[i][j] = sum[i - 1][j] + rowsum;
        }
    }
    double result = n * fun(n, 1, 1, 8, 8) - sum[8][8] * sum[8][8];
    cout << setiosflags(ios::fixed) << setprecision(3) << sqrt(result / (n * n)) << endl;
    return 0;
}
