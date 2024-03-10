#include <iostream>
#include <ctype.h>
using namespace std;

struct Point
{
	int x;
	int y;
};

int main()
{
	
	int n = 0;
	cin >> n;

	Point point[100];
	for (int i = 0; i < n; i++)
	{
		cin >> point[i].x >> point[i].y;
	}


	Point maxPoint[100];
	int num = 0; 
	for (int i = 0; i < n; i++)
	{
		bool isMaxPoint = true;
		for (int j = 0; j < n; j++)
		{
			if (j == i)
			{
				continue;
			}
			if (point[i].x <= point[j].x && point[i].y <= point[j].y)
			{
				isMaxPoint = false;
				break;
			}
		}
		if (isMaxPoint)
		{
			maxPoint[num++] = point[i];
		}
	}


	for (int i = 0; i < num; i++)
	{
		for (int j = 1; j < num; j++)
		{
			if (maxPoint[j - 1].x > maxPoint[j].x)
			{
				Point temp = maxPoint[j - 1];
				maxPoint[j - 1] = maxPoint[j];
				maxPoint[j] = temp;
			}
		}
	}


	for (int i = 0; i < num - 1; i++)
	{
		cout << "(" << maxPoint[i].x << "," << maxPoint[i].y << "),";
	}

	cout << "(" << maxPoint[num - 1].x << "," << maxPoint[num - 1].y << ")" << endl;
	return 0;
}