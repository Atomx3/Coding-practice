/*
3. C程序设计进阶
9. 第8周
3. 编程题＃3：Set
程序使用了 std::map 来跟踪每个整数的出现次数，
以及一个 std::set 来记录哪些数字已经被添加过。
*/

#include <iostream>
#include <map>
#include <set>
using namespace std;

int main() {
    int n;
    cin >> n;
    map<int, int> count; // 用于计数每个整数的出现次数
    set<int> added; // 用于记录是否添加过该整数

    while (n--) {
        string command;
        int x;
        cin >> command >> x;

        if (command == "add") {
            count[x]++;
            added.insert(x);
            cout << count[x] << endl;
        } else if (command == "del") {
            cout << count[x] << endl;
            count[x] = 0; // 删除所有x
        } else if (command == "ask") {
            cout << added.count(x) << " " << count[x] << endl;
        }
    }

    return 0;
}

