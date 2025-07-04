/*
3. C++程序设计
2. 第2 module
2. 简单的学生信息处理程序实现

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
在一个学生信息处理程序中，要求实现一个代表学生的类，并且所有成员变量都应该是私有的。

（注：评测系统无法自动判断变量是否私有。我们会在结束之后统一对作业进行检查，请同学们严格按照题目要求完成，否则可能会影响作业成绩。）

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

this solution is the most easy and simple one.
*/
#include <iostream>
#include <string>
using namespace std;

// Define a Student class
class Student
{
private:
    // Private member variables
    string name; // Student's name
    string id;   // Student's ID
    int age;     // Student's age
    int score1, score2, score3, score4; // Scores in four subjects
    int average; // Average score

public:
    // Public member functions
    void init();  // Function to initialize student data
    void print(); // Function to print student data
};

// Definition of the init function
void Student::init()
{
    char comma; // Variable to store the comma delimiter
    // Read the name until the first comma
    getline(cin, name, ',');
    // Read the age and the following comma
    cin >> age >> comma;
    // Read the ID until the next comma
    getline(cin, id, ',');
    // Read the four scores separated by commas
    cin >> score1 >> comma >> score2 >> comma >> score3 >> comma >> score4;
    // Calculate the average score
    average = (score1 + score2 + score3 + score4) / 4;
}

// Definition of the print function
void Student::print()
{
    // Print the student's data in the required format
    cout << name << ',' << age << ',' << id << ',' << average << endl;
}

int main()
{
    // Create an instance of the Student class
    Student stuWho;
    // Initialize the student's data
    stuWho.init();
    // Print the student's data
    stuWho.print();
    return 0;
}
