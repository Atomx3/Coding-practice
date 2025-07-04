/*
3. C++程序设计
2. 第2 module
2. 简单的学生信息处理程序实现

this solution is suitable for older versions of C++ standards.

1. Using char arrays: Replaced std::string with char arrays for name and id.
2. Using strtok and atoi: Replaced std::getline and std::stoi with strtok and atoi for parsing and converting input.
3. Simplified input handling: Ensured the input is parsed correctly using C-style string functions.

*/

#include <iostream>
#include <cstring> // for strtok and atoi
#include <cmath> // for floor
using namespace std;

class Student {
private:
    char name[50];
    int age;
    char id[20];
    int scores[4];

public:
    void input() {
        char input[100];
        cin.getline(input, 100);

        char* token = strtok(input, ",");
        strcpy(name, token);

        token = strtok(nullptr, ",");
        age = atoi(token);

        token = strtok(nullptr, ",");
        strcpy(id, token);

        for (int i = 0; i < 4; i++) {
            token = strtok(nullptr, ",");
            scores[i] = atoi(token);
        }
    }

    int calculateAverage() {
        int sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += scores[i];
        }
        return sum / 4; // integer division for rounding down
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
