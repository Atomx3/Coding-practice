/*
3. C程序设计进阶
8. 第8 module
1. 编程题＃1：

output:
1 2 6 7 8 9
*/

#include <iostream> 
#include <iterator> 
#include <set> 
using namespace std;

int main() { 
    int a[] = {8,7,8,9,6,2,1}; 
    set<int> v(a, a+7); // copy array into set
    ostream_iterator<int> o(cout," "); // output space
    copy( v.begin(),v.end(),o); // print elements and then with a space
    return 0;
}