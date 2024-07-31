/*
3. C程序设计进阶
2. 第2周
1. 编程题＃1：简单的学生信息处理程序实现
c++, class Student, variables in private,
char pointer, maybe float values(scores) output. 
*/

#include <iostream>
#include <cstring> 
#include <cmath> 

using namespace std;

class Student {
private:
    char* words[7]; // 二维指针数组，用于存储单词

public:
    void input() {
        char input[100];
        cin.getline(input, sizeof(input));

        // 使用 strtok 将输入的字符串拆分成单词
        char* token = strtok(input, ",");
        int i = 0;
        while (token != nullptr && i < 7) {
            words[i] = new char[strlen(token) + 1];
            strcpy(words[i], token);
            i++;
            token = strtok(nullptr, ",");
        }
    }
    // get average scores for a student.
    float calculate() { // return type could be int, if need int 
        float ave_scores = 0.0;
        //int ave_scores = 0;
        //stof, convert string to float. 
        ave_scores = (stof(words[3]) + stof(words[4]) + stof(words[5]) + stof(words[6]))/4;
        //stoi, convert string to int.
        //ave_scores = (stoi(words[3]) + stoi(words[4]) + stoi(words[5]) + stoi(words[6]))/4;
        
        // Round to one decimal place
        ave_scores = round(ave_scores * 10) / 10.0;

        return ave_scores;

    }

    void output() {
        // print the original data purely.
        // for (int i = 0; i < 7; i++) {
        //     cout << words[i] << endl;
        // }

        cout<<words[0]<<","<<words[1]<<","<<words[2];
        cout<<","<<calculate()<<endl;
    }

    // 提供公共方法以获取存储的单词
    // const char* getWord(int index) const {
    //     if (index >= 0 && index < 7) {
    //         return words[index];
    //     }
    //     return nullptr;
    // }

    ~Student() {
        // 释放内存
        for (int i = 0; i < 7; i++) {
            delete[] words[i];
        }
    }
};

int main() {
    Student student;
    student.input();
    student.calculate(); 
    student.output();

    return 0;
}

