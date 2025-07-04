/*
3. C程序设计进阶
10. 第10 module
6. 编程题＃6：MyString

input：none
output：
1. abcd-efgh-abcd-
2. abcd-
3.
4. abcd-efgh-
5. efgh-
6. c
7. abcd-
8. ijAl-
9. ijAl-mnop
10. qrst-abcd-
11. abcd-qrst-abcd- uvw xyz
about
big
me
take
abcd
qrst-abcd-

程序解释：
函数qsort对 SArray数组排序，它多次调用CompareString函数来比较数组中的元素；
每次传递两个元素的地址给CompareString，这些元素地址分别存储在e1和e2中。

在CompareString函数内部，e1和e2被转换为MyString*类型的指针，
这样就可以使用MyString类的比较操作符来比较两个字符串对象的值；

*/

#include <cstring>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace std;

class MyString : public string {
public: // 三种构造函数，初始化基类部分
    // 默认构造函数，无参
    MyString() : string() {}
    // 从C风格字符串到MyString对象的转换构造函数
    MyString(const char* str) : string(str) {}
    // 拷贝构造函数，复制string对象，创建新的MyString对象
    MyString(const string& str) : string(str) {}

    // 重载+操作符，用于连接2个MyString对象类型的字符串
    // string(rhs)将rhs转换为基类 string类型
    MyString operator+(const MyString& rhs) const {
        return MyString(string(*this) + string(rhs));
    }
    // 重载+操作符，用于连接MyString对象和C风格字符串
    MyString operator+(const char* rhs) const {
        return MyString(string(*this) + rhs);
    }
    // 重载[]操作符，用于索引访问
    char &operator[](int index)
    {
        return string::operator[](index);
    }
    // 重载()操作符，用于提取子串
    MyString operator()(int start, int length) const {
        return MyString(this->substr(start, length));
    }
};

int CompareString( const void * e1, const void * e2)
{// qsort排序算法传递参数e1和e2，其指向SArray数组元素的指针；
        MyString * s1 = (MyString * ) e1;
        MyString * s2 = (MyString * ) e2;
        if( * s1 < *s2 )
                 return -1;
        else if( *s1 == *s2)
                 return 0;
        else if( *s1 > *s2 )
                 return 1;
}

int main()
{
        MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
        MyString SArray[4] = {"big","me","about","take"};
        cout << "1. " << s1 << s2 << s3<< s4<< endl;
        s4 = s3;
        s3 = s1 + s3;
        cout << "2. " << s1 << endl;
        cout << "3. " << s2 << endl;
        cout << "4. " << s3 << endl;
        cout << "5. " << s4 << endl;
        cout << "6. " << s1[2] << endl;
        s2 = s1;
        s1 = "ijkl-";
        s1[2] = 'A' ;
        cout << "7. " << s2 << endl;
        cout << "8. " << s1 << endl;
        s1 += "mnop";
        cout << "9. " << s1 << endl;
        s4 = "qrst-" + s2;
        cout << "10. " << s4 << endl;
        s1 = s2 + s4 + " uvw " + "xyz";
        cout << "11. " << s1 << endl;
//sizeof(MyString)= sizeof(string）具体实现依赖于编译器和标准库定义
        qsort(SArray,4,sizeof(MyString),CompareString);
        for( int i = 0;i < 4;i ++ )
            cout << SArray[i] << endl;// 排序后输出整个SArray数组
        // 重载 operator()操作符，提取子串
        //s1的从下标0开始长度为4的子串
        cout << s1(0,4) << endl;
        //s1的从下标5开始长度为10的子串
        cout << s1(5,10) << endl;
        return 0;
}