/*
3. C++程序设计
2. 第2 module
2. 简单的学生信息处理程序实现

c++, class structure, variables in private,
char pointer, maybe float values(scores) output. 


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
