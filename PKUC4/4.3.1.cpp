/*
4. 算法基础
3. 第3周
1. 编程题＃1： 完美覆盖

国际象棋棋盘有8x8=64个方格，每張多米诺牌覆盖棋盘上相邻的两个方格，
任何两张多米诺牌均不重叠，棋盘被32張多米诺牌完美覆盖，有很多種不同覆蓋方式；

用程序對3乘n個棋盘的不同的完美覆盖方式的总数进行计算，
輸入n，輸出覆盖方式的數量，當輸入-1時，程序停止。

數據案例
輸入 
2
8
12
-1

輸出
3
153
2131
*/


#include <iostream>
#include <cstring>
using namespace std;

int res[31];

int f(int n) // 递归函数
{
	if (n == 0)
	{
		return 1;
	}
    if (n == 1)
	{
		return BASE_CASE_1;
	}
	if (n == 2)
	{
		return 3;
	}
    if (n == 3)
	{
		return BASE_CASE_3;
	}
	if (res[n] != -1)
	{
		return res[n];
	}
	else// 记忆化搜索
	{// 如果 res[n] 的值是 -1
		int tmp = 4 * f(n - 2) - f(n - 4);
		res[n] = tmp;// 计算结果存储在 res[n] 中
		return tmp;
	}
}

int main()
{// C/C++标准库函数memset,将-1复制到数组res中的每个元素。
	memset(res, -1, sizeof(res));
	int n;
	while (cin >> n && n != -1)
	{
		cout << f(n) << endl;
	}
	return 0;
}