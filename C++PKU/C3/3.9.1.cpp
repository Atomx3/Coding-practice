/*
3. C程序设计进阶
9. 第8 module
1. 编程题＃1：

不使用 binary_search。
使用两个嵌套循环来遍历所有点对，并检查是否可以从这些点中形成标准矩形。
这段代码通过遍历点集 v 来查找与当前点 i 和 j 形成矩形的另外两个点.
这种方法可能比使用 binary_search 效率低，
特别是当点集非常大时，因为它需要对每对点进行多次迭代。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Point {
    int x;
    int y;
    Point(int x_,int y_):x(x_),y(y_) { }
};
bool operator < ( const Point & p1, const Point & p2)
{   
    if( p1.y < p2.y )
        return true;
    else if( p1.y == p2.y )
        return p1.x < p2.x;
    else
        return false;
}

int main()
{
    int t;
    int x,y;
    cin >> t;
    vector<Point> v;
    while( t -- ) { // Read input and populate v 
        cin >> x >> y;
        v.push_back(Point(x,y));
    }

    vector<Point>::iterator i,j;
    int nTotalNum = 0;
    // 在此处补充你的代码, 其他位置禁止改代码
    for (i = v.begin(); i < v.end()-1; i++) {
        for (j = i + 1; j < v.end(); j++) {
            // 确保我们选择的是对角线上的点
            if(i->x != j->x && i->y != j->y) {
                // 检查是否存在其他两个点使得可以形成矩形
                bool found_p1 = false;
                bool found_p2 = false;
                for (auto& p : v) {
                    if (p.x == i->x && p.y == j->y) found_p1 = true;
                    if (p.x == j->x && p.y == i->y) found_p2 = true;
                }
                // 如果找到了其他两个点，则增加计数
                if (found_p1 && found_p2) nTotalNum++;
            }
        }
    }
    cout << nTotalNum / 2 << endl; // 每个矩形被计数两次，所以结果要除以2

    return 0;

}