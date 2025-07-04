/*
程序反复出现compile error的提示，经过分析发现由于考试编译器为2011年之前的版本。
因此，我们重新修改了代码，使其符合旧版本编译器需求。

1. **问题根源**：
   - 最初的问题是因为代码使用了C++11特有的函数(`stoi`和`to_string`)和语法(范围for循环)
   - 这些特性在旧版编译器上不被支持

2. **为何现在能通过编译**：
   - 我们已经做了以下兼容性修改：
     - 用自定义的`StringtoNum`替代`stoi`
     - 用自定义的`NumToString`替代`to_string`
     - 将范围for循环改为传统for循环
   - 这些修改使代码符合C++98/C++03标准

3. **当前状态**：
   - 编译时只产生警告(关于C++11扩展)，而不是错误
   - 警告不会阻止程序编译和运行
   - 程序功能保持不变

4. **进一步建议**：
   - 如果想完全消除警告，可以添加编译选项`-Wno-c++11-extensions`
   - 或者确保所有循环都使用传统形式
   - 但当前的警告不影响程序功能
        
*/

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

string str[21]; // 存储字符串，最多20个（下标1~20）
int NumOfStr = 0; // 字符串数量

// 判断字符串是否为纯数字
bool isNum(string s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (!isdigit(s[i]))
		{
			return false;
		}
	}
	return true;
}

// 查找字符s在第n个字符串中的第一次出现位置
int find()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].find(s);
}

// 查找字符s在第n个字符串中的最后一次出现位置
int rfind()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].rfind(s);
}

// 获取一个整数，可以是数字或find/rfind表达式
// 自定义字符串转数字函数
// Replace the range-based for loop with traditional iteration
int StringtoNum(const string& s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char c = s[i];
        if (isdigit(c)) {
            num = num * 10 + (c - '0');
        }
    }
    return num;
}

// 自定义数字转字符串函数
string NumToString(int num) {
    if (num == 0) return "0";
    string s;
    bool negative = false;
    if (num < 0) {
        negative = true;
        num = -num;
    }
    while (num > 0) {
        s = char(num % 10 + '0') + s;
        num /= 10;
    }
    if (negative) s = "-" + s;
    return s;
}

// 修改get_int函数
int get_int()
{
    string str;
    cin >> str;
    if (isNum(str))
    {
        return StringtoNum(str);
    }
	else
	{
		if (str == "find")
		{
			return find();
		}
		else if (str == "rfind")
		{
			return rfind();
		}
	}
	return 0;
}

// 从第n个字符串的x位置起，截取长度为l的子串
string copy()
{
	int n, x, l;
	n = get_int();
	x = get_int();
	l = get_int();
	return str[n].substr(x, l);
}

string add(); // 前置声明

// 获取一个字符串，可以是普通字符串、copy或add表达式
string get_str()
{
	string str;
	cin >> str;
	if (str == "copy")
	{
		return copy();
	}
	else if (str == "add")
	{
		return add();
	}
	else
	{
		return str;
	}
}

// 字符串加法：若两个字符串均为0~99999的数字，则做整数加法，否则做字符串拼接
string add()
{
	string s1 = get_str();
	string s2 = get_str();
	if (isNum(s1) && isNum(s2) && StringtoNum(s1) >= 0 && StringtoNum(s1) <= 99999 && StringtoNum(s2) >= 0 && StringtoNum(s2) <= 99999)
	{
		return NumToString(StringtoNum(s1) + StringtoNum(s2));
	}
	else
	{
		return s1 + s2;
	}
}

// 在第n个字符串的x位置插入字符串s
void insert()
{
	string s = get_str();
	int n = get_int();
	int x = get_int();
	str[n].insert(x, s);
}

// 将第n个字符串重置为s
void reset()
{
	string s = get_str();
	int n = get_int();
	str[n] = s;
}

// 输出第n个字符串
void print()
{
	int n = get_int();
	cout << str[n] << endl;
}

// 输出所有字符串
void printall()
{
	for (int i = 1; i <= NumOfStr; i++)
	{
		cout << str[i] << endl;
	}
}

int main()
{
	cin >> NumOfStr; // 输入字符串数量
	for (int i = 1; i <= NumOfStr; i++)
	{
		cin >> str[i]; // 输入每个字符串
	}
	while (true)
	{
		string operation;
		cin >> operation;
		if (operation == "insert")
		{
			insert();
		}
		else if (operation == "reset")
		{
			reset();
		}
		else if (operation == "print")
		{
			print();
		}
		else if (operation == "printall")
		{
			printall();
		}
		else if (operation == "over")
		{
			break;
		}
	}
	return 0;
}

