
/*
3. C程序设计进阶
9. 第8 module  
4. 编程题#4: 字符串操作
the same subject as 3.7.4.cpp
but this one is failed, and will be improved.

本案例的正确解决方案应该采纳递归法,例如:  
insert copy 1 find 2 1 2 2 2
从输入的命令行的右侧向左侧处理字符串。
insert (copy(1,find(2 ,1),2),2,2)
please debug and make sure below test result.

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
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Helper functions
int toInt(const string& s) {
  stringstream ss(s);
  int num;
  if (ss >> num) return num;
  return -1;
}

string add(const string& s1, const string& s2) {
  int num1 = toInt(s1), num2 = toInt(s2);
  if (num1 != -1 && num2 != -1) return to_string(num1 + num2);
  else return s1 + s2;
}

int find(const vector<string>& strings, const string& value, int N) {
  if (N - 1 < strings.size()) {
    size_t pos = strings[N - 1].find(value);
    return pos != string::npos ? pos : strings[N - 1].length();
  }
  return -1; // 如果N无效,返回-1
}


int rfind(const vector<string>& strings, const string& value, int N) {
  size_t pos = strings[N - 1].rfind(value);
  return pos != string::npos ? pos : strings[N - 1].length();
}

string copy(const vector<string>& strings, int N, int X, int L) {
  if (N - 1 < strings.size()) {
    const string& str = strings[N - 1];
    if (X < str.length() && X + L <= str.length()) {
      return str.substr(X, L);
    }
  }
  return "";
}

void insert(vector<string>& strings, const string& S, int N, int X) {
  if (N > 0 && N <= strings.size() && X >= 0 && X <= strings[N - 1].length() && !S.empty()) {
    strings[N - 1].insert(X, S);
  }
}

void reset(vector<string>& strings, const string& S, int N) {
  if (N - 1 < strings.size()) {
    strings[N - 1] = S;
  }
}

void print(const vector<string>& strings, int N) {
  if (N - 1 < strings.size()) {
    cout << strings[N - 1] << endl;
  }
}

void printall(const vector<string>& strings) {
  for (const string& str : strings) {
    cout << str << endl;
  }
}

// Recursive function to process commands  
string processCommand(vector<string>& strings, istringstream& iss) {

  string command;
  iss >> command;

  if (command == "copy") {
    int N, X, L;
    iss >> N >> X >> L;
    return copy(strings, N, X, L);

  } else if (command == "add") {
    string S1 = processCommand(strings, iss); 
    string S2 = processCommand(strings, iss);
    return add(S1, S2);

  } else if (command == "find") {
    string S;
    int N;
    iss >> S >> N;
    return to_string(find(strings, S, N));

  } else if (command == "rfind") {
    string S; 
    int N;
    iss >> N;
    return to_string(rfind(strings, S, N));

  } else {
    // Handle other commands
    return ""; 
  }

}

int main() {
  int n;
  cin >> n;
  vector<string> strings(n);
  for (int i = 0; i < n; ++i) {
    cin >> strings[i]; 
  }

  string line;
  while (getline(cin, line) && line != "over") {
    istringstream iss(line);
    string command;
    iss >> command;
    
    if (command == "insert") {
      //...insert code
    }
    else if (command == "reset") {
       string S = processCommand(strings, iss);
       int N;
       iss >> N;
       reset(strings, S, N);
    } 
    else if (command == "print") {
      int N;
      iss >> N;
      print(strings, N);
    }
    else if (command == "printall") {
      printall(strings); 
    }
  }

  return 0;
}
