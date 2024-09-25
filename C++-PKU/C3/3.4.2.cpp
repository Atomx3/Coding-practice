/*
3. C++程序设计
4. 第4周
2. 编程题＃2：
重载函数代码全部放进 MyInt类内部,
MyInt的成员函数里不允许使用静态变量。

input

output
4，1
*/

#include <iostream>
using namespace std;

class MyInt {
  int nVal;
public:
  
  MyInt(int n) {nVal = n;}
  int ReturnVal() {return nVal;}
 
  MyInt & operator-(int n) {
      nVal -= n;
      return *this;
  }

};

int main () {
    MyInt objInt(10);
    objInt-2-1-3;
    cout << objInt.ReturnVal();
    cout <<",";
    objInt-2-1;
    cout << objInt.ReturnVal();
    return 0;
}

