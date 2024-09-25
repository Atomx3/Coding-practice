/*
3. C程序设计进阶
10. 第10周
5. 编程题＃5：计算数组的低3位之和

输入一个正整数构成的数组a[0], a[1], a[2], ... , a[n-1],
计算它们的二进制低3位之和。

输入
数组a,以0表示输入结束。
1 3 9 7 3 6 20 15 18 17 4 8 18 0

输出
一个整数 , 所输入数组各元素的二进制低3位之和。
41

代码解释
1. void operator()(int n) 
vec容器中的每个元素v，通过CMy_add类的实例传入operator()(int n)方法中，
for_each算法遍历每个v，并对每个元素调用operator()方法，
此时传入的参数n就是vec中的当前元素v。

2. CMy_add(int& s) : sum(s) {} 
my_sum在CMy_add类的上下文中作为sum来作用，它们是同一个数据的两个别名。
my_sum变量是作为引用传递给CMy_add类的构造函数的。
这里的my_sum变量通过构造函数CMy_add(int& s)传递给私有成员变量int& sum。
这意味着sum变量是对my_sum变量的引用，它们指向同一个内存地址，
所以对sum的任何修改都会直接影响my_sum。

3. for_each(vec.begin(), vec.end(), CMy_add(my_sum));
当创建一个类的实例并将其用作函数对象时，这个实例本身通常没有一个特定的“对象名”。
CMy_add类的实例是匿名的，它直接在for_each函数调用中创建并使用。
这个实例没有赋给一个变量名，因此没有一个可以引用的对象名。

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class CMy_add {
private:
    int& sum; // 引用，用于存储和更新总和
public:
    CMy_add(int& s) : sum(s) {} // 构造函数

    void operator()(int n) {
        sum += (n & 0x7); // 将n的二进制低3位加到sum
    }
};

int main(int argc, char* argv[]) {
        int v, my_sum=0;
        vector<int> vec;
        cin>>v;
        while ( v ) {
                vec.push_back(v);
                cin>>v;
        }
        // 使用CMy_add类的实例来更新my_sum
        for_each(vec.begin(), vec.end(), CMy_add(my_sum));
        cout << my_sum << endl; // 输出最终的总和
        return 0;
}