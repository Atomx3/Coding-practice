/*
3. C程序设计进阶
9. 第8 module
2. 编程题＃2：

写一个自己的 CMyistream_iterator 模板，
使之能和 istream_iterator 模板达到一样的效果，即：

输入：
79 90 20 hello me

输出：
79

79,90,20

hello,me
*/

#include <iostream>
#include <string>
using namespace std;

template <class T>
class CMyistream_iterator {
    istream* p;
    T value;
    bool end;
public:
    CMyistream_iterator() : p(nullptr), end(true) {} // 构造尾后迭代器
    CMyistream_iterator(istream& in) : p(&in), end(false) { ++(*this); }
    //dereference operator
    T operator*() const { return value; }
    T* operator->() { return &value; }
    //pre-increment operator
    CMyistream_iterator& operator++() {
        if (p && !p->eof()) {
            *p >> value;
        } else {
            end = true;
        }
        return *this;
    }
    //post-increment operator
    CMyistream_iterator operator++(int) {
        CMyistream_iterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const CMyistream_iterator& it) const {
        return (p == it.p && end == it.end);
    }

    bool operator!=(const CMyistream_iterator& it) const {
        return !(*this == it);
    }
};


int main()
{
    CMyistream_iterator<int> inputInt(cin);
    int n1,n2,n3;
    n1 = * inputInt; //读入 n1
    int tmp = * inputInt;
    cout << tmp << endl;
    inputInt ++;
    n2 = * inputInt; //读入 n2
    inputInt ++;
    n3 = * inputInt; //读入 n3
    cout << n1 << "," << n2<< "," << n3 << endl;
    CMyistream_iterator<string> inputStr(cin);
    string s1,s2;
    s1 = * inputStr;
    inputStr ++;
    s2 = * inputStr;
    cout << s1 << "," << s2 << endl;
    return 0;
}