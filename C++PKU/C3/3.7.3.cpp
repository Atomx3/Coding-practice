/*
3. C程序设计进阶
7. 第7 module
3. 编程题＃3：整数的输出格式
manipulators: 
hex
dec
setw(0)
setfill('0')

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	int integer;
	cin >> integer;

	cout << hex << integer << endl;
	cout << dec << setw(10) << setfill('0') << integer << endl;
	return 0;
}