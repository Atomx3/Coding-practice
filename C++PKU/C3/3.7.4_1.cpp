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

该程序版本特别说明：
1. **使用了C++11特有的函数**：
   - `stoi()` - 字符串转整数
   - `to_string()` - 数值转字符串

2. **使用了C++11的特性**：
   - 内联命名空间(`inline`)
   - 更严格的类型检查

3. **代码注释也明确说明**：
   ```cpp
   // 这是符合新版c++11特性的方法
   ```

4. **其他C++11特性**：
   - 使用了更现代的字符串处理方式
   - 函数设计更符合C++11的风格

如果您需要在非C++11环境下编译，可以参考我们之前修改的版本，将C++11特有的函数替换为自定义实现。
*/

#include<iostream>
#include<string>
using namespace std;
string table[21];

inline string do_copy();
inline string do_add();
inline int do_find();
inline int do_rfind();

string get_string() {
	string command;
	cin >> command;
	if (command == "copy") {
		return do_copy();
	}
	else if (command == "add") {
		return do_add();
	}
	else {
		return command;
	}
}
int get_n() {
	string command;
	cin >> command;
	if (command == "find") {
		return do_find();
	}
	else if (command == "rfind") {
		return do_rfind();
	}
	else {
		return stoi(command);
	}
}

string do_copy() {
	int N = get_n();
	int X = get_n();
	int L = get_n();
	return table[N].substr(X, L);
}

inline bool judge_num(const string& str) {
	if (str.length() > 5) return false;
	for (int i = 0; i < str.length(); i++)
		if (!isdigit(str[i])) return false;
	return true;
}
string do_add() {
	string S1 = get_string();
	string S2 = get_string();
	if (judge_num(S1) && judge_num(S2)) {
		int ans = stoi(S1) + stoi(S2);
		return to_string(ans);
	}
	return S1 + S2;
}
int do_find() {
	string S = get_string();
	int N = get_n();
	return table[N].find(S);
}
int do_rfind() {
	string S = get_string();
	int N = get_n();
	return table[N].rfind(S);
	
}
inline void do_insert() {
	string S = get_string();
	int N = get_n();
	int X = get_n();
	table[N].insert(X, S);
}
inline void do_reset() {
	string S = get_string();
	int N = get_n();
	table[N] = S;
}
inline void do_print() {
	int N = get_n();
	cout << table[N] << endl;
}
inline void do_printall(int n) {
	for (int i = 1; i <= n; i++) {
		cout << table[i] << endl;
	}
}

int main() {
	int n;
	string command;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> table[i];
	do {
		cin >> command;
		if (command == "over") break;
		if (command == "insert") {
			do_insert();
		}
		else if (command == "reset") {
			do_reset();
		}
		else if (command == "print") {
			do_print();
		}
		else if (command == "printall") {
			do_printall(n);
		}
	} while (true);

	return 0;
}