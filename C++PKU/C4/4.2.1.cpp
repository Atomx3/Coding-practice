/*
4. 算法基础
2. 第2 module
1. 编程题＃1： 画家问题

写一个c++程序，解决以下问题：
N*N个正方形的砖组成的墙，其中的砖为白色或黄色，现在需要把所有的白色砖也涂成黄色。
由于画笔不好用，当涂画第(i, j)位置的砖时， 无论之前这些砖是什么颜色，
(i, j)及其 module围(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)的砖都会变成黄色。
请计算，最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色。

首行输入整数N，下方为N*N的砖头矩阵，其中的元素为初始状态的砖头颜色，
由字符y或w表示，字符中间无空格，砖头的黄色用字符y表示，白色用w表示。

输入数据案例：
5
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww
wwwwwwwwwwwwwww

输出数据案例：
15
至少涂15块砖可以将以上的25块砖都变成黄色。
如果不能将所有的砖都涂成黄色，则输出“inf”

误解题目：请确保常识，一旦砖块变为黄色，就不会再被涂回白色，
所以，我不理解，对于有限的整数N，为何会有输出inf的无解答案?
这不是灯开关问题，按第二次，开关恢复到原来状态，用一种颜色涂画墙面是不可逆的过程。
*/

#include <iostream>
#include <cmath>
using namespace std;

int wall[17][17], paint[17][17];
int width;
int minCount;

int Count()
{
	int sum = 0;
	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			sum += paint[i][j];
		}
	}
	return sum;
}

// 初始化数组和处理输入
void init()
{
	for (int i = 0; i < 17; i++)
	{
		for (int j = 0; j < 17; j++)
		{
			wall[i][j] = 0;
			paint[i][j] = 0;
		}
	}

	for (int i = 1; i <= width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			char tmp;
			cin >> tmp;
			switch (tmp)
			{
			case 'y':
				wall[i][j] = 0;
				break;
			case 'w':
				wall[i][j] = 1;
				break;
			}
		}
	}
}

// 验证答案是否正确，主要验证最后一行
bool guess()
{
	for (int j = 1; j <= width; j++)
	{
		if ((paint[width][j - 1] + paint[width][j] + paint[width][j + 1] + paint[width - 1][j]) % 2 != wall[width][j])
			return false;
	}
	return true;
}

// 根据第一行的枚举更新剩余几行
void update()
{
	for (int i = 1; i < width; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			paint[i + 1][j] = (wall[i][j] + paint[i][j] + paint[i][j - 1] + paint[i][j + 1] + paint[i - 1][j]) % 2;
		}
	}
}

// 枚举第一行的所有情况，直到得出答案
void enumerate()
{
	// 初始情况
	update();

	for (int i = 0; i < pow(2, width); i++)
	{
		if (guess())
		{
			int count = Count();
			if (count < minCount)
			{
				minCount = count;
			}
		}
		paint[1][1]++;
		int k = 1;
		while (paint[1][k] > 1) // 进位
		{
			paint[1][k] = 0;
			paint[1][++k]++;
		}
		update();
	}
}

int main()
{
	int ncase;
	cin >> ncase;
	
	for (int i = 0; i < ncase; i++)
	{
		cin >> width;
		minCount = 226; // 最大15*15 = 225
		init();
		enumerate();

		if (minCount == 226)
		{
			cout << "inf" << endl;
		}
		else
		{
			cout << minCount << endl;
		}
	}
}
