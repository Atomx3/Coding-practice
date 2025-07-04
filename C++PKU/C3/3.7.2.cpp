/*
3. C程序设计进阶
7. 第7 module
2. 编程题＃2：实数的输出格式
stream manipulator
positive real number, double type
scientific float-point notation
manipulator: setprecision
*/
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	double real;
	cin >> real;

	cout << fixed << setprecision(5) << real << endl;
	cout << scientific << setprecision(7) << real << endl;
	return 0;
}