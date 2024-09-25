/*
3. C++程序设计
2. 第2周
2. 简单的学生信息处理程序实现
c++, class Student, variables in private,
char pointer, maybe float values(scores) output. 

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个学生信息处理程序中，要求实现一个代表学生的类，并且所有成员变量都应该是私有的。

（注：评测系统无法自动判断变量是否私有。我们会在结束之后统一对作业进行检查，
请同学们严格按照题目要求完成，否则可能会影响作业成绩。）

输入
姓名，年龄，学号，第一学年平均成绩，第二学年平均成绩，第三学年平均成绩，第四学年平均成绩。

其中姓名、学号为字符串，不含空格和逗号；年龄为正整数；成绩为非负整数。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

输出
一行，按顺序输出：姓名，年龄，学号，四年平均成绩（向下取整）。

各部分内容之间均用单个英文逗号","隔开，无多余空格。

样例输入
Tom,18,7817,80,80,90,70

样例输出
Tom,18,7817,80

*/
#include <iostream>
#include <string>
#include <cmath> // for floor
using namespace std;

class Student {
private:
    string name;
    int age;
    string id;
    int scores[4];

public:
    void input() {
        string input;
        getline(cin, input);

        size_t pos = 0;
        string token;
        int index = 0;

        while ((pos = input.find(',')) != string::npos) {
            token = input.substr(0, pos);
            if (index == 0) name = token;
            else if (index == 1) age = stoi(token);
            else if (index == 2) id = token;
            else scores[index - 3] = stoi(token);
            input.erase(0, pos + 1);
            index++;
        }
        scores[index - 3] = stoi(input); // last score
    }

    int calculateAverage() {
        int sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += scores[i];
        }
        return floor(sum / 4.0); // floor to get the integer part
    }

    void output() {
        cout << name << "," << age << "," << id << "," << calculateAverage() << endl;
    }
};

int main() {
    Student student;
    student.input();
    student.output();

    return 0;
}
