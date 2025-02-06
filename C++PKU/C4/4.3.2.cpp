/*
4. 算法基础
3. 第3周
2. 编程题＃2： 文件结构“图”

输入
file1
file2
dir3
dir2
file1
file2
]
]
file4
dir1
]
file3
*
file2
file1
*
#

输出
DATA SET 1:
ROOT
|        dir3
|        |        dir2
|        |        file1
|        |        file2
|        dir1
file1
file2
file3
file4

DATA SET 2:
ROOT
file1
file2
*/

#include <iostream>
#include <string>
#include <set>
#include <vector>
using namespace std;

void printItem(int hierarchy, const string& item) {
    for (int i = 0; i < hierarchy; i++) {
        cout << "|        ";
    }
    cout << item << endl;
}

// 递归函数，用于展示文件和目录
void presentFile(int hierarchy, set<string>& files, vector<string>& dirs) {
    // 先输出所有文件，因为文件需要按字典顺序排列
    for (const auto& file : files) {
        printItem(hierarchy, file);
    }
    files.clear(); // 清空文件集合以供下一次使用

    // 输出所有目录，并递归地调用自身来处理子目录
    while (!dirs.empty()) {
        string curDir = dirs.back();
        dirs.pop_back();
        printItem(hierarchy, curDir);
        presentFile(hierarchy + 1, files, dirs); // 递归调用
    }
}

int main() {
    // freopen("out.txt", "w", stdout); // Uncomment if output to file is needed
    int dataSetCount = 1;
    string item;
    set<string> files;
    vector<string> dirs;
    bool newDataSet = false;

    while (cin >> item) {
        if (item == "*") {
            cout << "DATA SET " << dataSetCount << ":" << endl;
            cout << "ROOT" << endl;
            presentFile(1, files, dirs);
            cout << endl;

            dataSetCount++;
            newDataSet = true;
        } else if (item == "#") {
            break;
        } else if (item[0] == 'f') {
            files.insert(item);
        } else if (item[0] == 'd') {
            dirs.push_back(item);
            newDataSet = false;
        } else if (item == "]" && !newDataSet) {
            presentFile(1, files, dirs); // 递归处理目录结束
        }
    }
    return 0;
}
