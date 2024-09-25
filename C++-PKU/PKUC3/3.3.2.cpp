/*
3. C++程序设计
3. 第3周
2. 编程题＃2：
*/
#include <iostream>
using namespace std;

class Sample{
public:
    int v;
    Sample(int n):v(n) { }
    //copy constructor.
    Sample(const Sample& other) {
            v = other.v * 2;
    }
    ~Sample(){}
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}
