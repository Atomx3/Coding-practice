/*
3. C程序设计进阶
7. 第7 module
4. 编程题＃4：字符串操作
manipulators: 
recursive functions from right to left: 
insert copy 1 find 2 1 2 2 2 
insert (copy(1,find(2 ,1),2),2,2) 

reset add copy 1 find 3 1 3 copy 2 find 2 2 2 3
reset( (add (  copy( 1, find( 3, 1), 3) , copy( 2, find(2, 2), 2)  ), 3)

find(2 ,1) = 2;
copy(1,2,2) = 29(string);
insert(29, 2, 2) = 

input: 
3
329strjvc
Opadfk48
Ifjoqwoqejr
insert copy 1 find 2 1 2 2 2 
print 2
reset add copy 1 find 3 1 3 copy 2 find 2 2 2 3
print 3
insert a 3 2
printall
over

output
Op29adfk48
358
329strjvc
Op29adfk48
35a8
*/

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

string str[21];
int NumOfStr = 0;

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

int find()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].find(s);
}

int rfind()
{
	char s;
	int n;
	cin >> s >> n;
	return str[n].rfind(s);
}

int get_int()
{
	string str;
	cin >> str;
	if (isNum(str))
	{
		return stoi(str);
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



string copy()
{
	int n, x, l;
	n = get_int();
	x = get_int();
	l = get_int();
	return str[n].substr(x, l);
}

string add();

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

string add()
{
	string s1 = get_str();
	string s2 = get_str();
	if (isNum(s1) && isNum(s2) && stoi(s1) >= 0 && stoi(s1) <= 99999 && stoi(s2) >= 0 && stoi(s2) <= 99999)
	{
		return to_string(stoi(s1) + stoi(s2));
	}
	else
	{
		return s1 + s2;
	}
}



void insert()
{
	string s = get_str();
	int n = get_int();
	int x = get_int();
	str[n].insert(x, s);
}

void reset()
{
	string s = get_str();
	int n = get_int();
	str[n] = s;
}

void print()
{
	int n = get_int();
	cout << str[n] << endl;
}

void printall()
{
	for (int i = 1; i <= NumOfStr; i++)
	{
		cout << str[i] << endl;
	}
}

int main()
{
	cin >> NumOfStr;
	for (int i = 1; i <= NumOfStr; i++)
	{
		cin >> str[i];
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

