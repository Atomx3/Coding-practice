// 03_最高的分数
#include <iostream>
using namespace std;

int main()
{
	int score = 0;
	int n = 0;
	cin >> n;

	int max = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> score;
		if (score > max)
		{
			max = score;
		}
	}
	cout << max << endl;
	return 0;
}