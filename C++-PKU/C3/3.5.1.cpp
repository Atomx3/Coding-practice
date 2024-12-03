/*
3. C++程序设计
5. 第5周
1. 编程题＃1：

class MyString, 4 object (s1,s2,s3,s4),
string type argument, private object,
=, +, += operators

*/

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class MyString: public string
{
public:
    // 默认构造函数
    MyString():string() {}
    // 用C风格字符串构造
    MyString(const char* str):string(str) {}
    // 用string对象构造
    MyString(const string& str):string(str) {}
    
    // 实现子串提取操作符()，用于获取指定位置和长度的子串
    MyString operator()(int start, int length) {
        return substr(start, length);
    }
    
    // 重载+=操作符，用于字符串追加
    MyString& operator+=(const char* str) {
        string::operator+=(str);
        return *this;
    }
};

// 重载全局+操作符，实现C风格字符串和MyString对象的连接
MyString operator+(const char* str, const MyString& s) {
    return MyString(string(str) + string(s));
}

// 比较函数，用于qsort排序
int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
     // 使用string类继承来的比较操作符
    if( *s1 < *s2 )     return -1;
    else if( *s1 == *s2 ) return 0;
    else if( *s1 > *s2 ) return 1;
    return 0;
}

int main() {
    // 创建4个MyString对象，使用不同的构造方式
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    
    // 创建MyString数组并初始化
    MyString SArray[4] = {"big","me","about","take"};
    
    // 测试字符串连接和输出
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    
    // 测试赋值操作和+操作符
    s4 = s3;    s3 = s1 + s3;
    
    // 测试各个对象的当前值
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    
    // 测试下标访问操作符
    cout << "6. " << s1[2] << endl;
    
    // 测试赋值和字符修改
    s2 = s1;    s1 = "ijkl-";
    s1[2] = 'A' ;
    
    // 测试字符串追加操作, s1= abcd- qrst- abcd- uvw xyz
    s1 += "mnop"; 
    
    // 测试C风格字符串和MyString对象的连接
    s4 = "qrst-" + s2;
    
    // 测试复杂的字符串连接
    s1 = s2 + s4 + " uvw " + "xyz";
    
    // 使用qsort对字符串数组进行排序
    qsort(SArray,4,sizeof(MyString), CompareString);
    
    // 输出排序后的数组
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
        
    // 测试子串提取功能
    cout << s1(0,4) << endl;
    cout << s1(5,10) << endl;
    return 0;
}