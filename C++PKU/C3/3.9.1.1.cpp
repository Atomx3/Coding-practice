/*
3. C程序设计进阶
9. 第8 module
1. 编程题＃：

程序用枚举法解决如下问题：
“标准矩形”的定义为，其边平行于平面上的坐标轴。
给程序输入整数n，然后输入不重复的 n 个点, 其横、纵坐标(x, y)为整数，
从这n个点中任取不重复的4个点，作为顶点所构成的四边形中，求标准矩形的个数？
The program uses enumeration to solve the following problems:
definition of a standard rectangle, Its sides are parallel to the coordinate axis on the plane.
input program int n, it's the number of the points on the coordinate axis, 
Its horizontal and vertical coordinates (x, y) are integers.
Select any 4 non-repeating points from n points,
To form a standard rectangle, count the number of standard rectangles.

code style: 
    _____________________;
    for( i = v.begin(); i < v.end() - 1;i ++ )
        for(_____________; ______________; _____________) {
            if(binary_search(v.begin(),v.end(),Point( j->x, i->y)) &&
                ____________________________________________ &&
                ____________________________________________ &&
                ____________________________________________ )
                nTotalNum ++;
        }
    cout << _________________;

注意：在程序中输入每个点的参数格式为(x y)，两个参数之间以一个空格分隔。



Note: The parameter format of each point（x y）
input square number n， 
then input n points（x y）with space between x and y as below.

data example 
input: 
6
2 3
2 5
4 5
4 4
2 4
4 3

output: 3

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
    int x, y;
    cin >> t;
    vector<Point> v;
    while (t--)
    { // Read input and populate v
        cin >> x >> y;
        v.push_back(Point(x, y));
    }

    vector<Point>::iterator i, j;
    int nTotalNum = 0;
    // only add code below, don't change other parts of  the program
    // 对点集进行排序，这是为了后续能够使用 binary_search
    sort(v.begin(), v.end()); 
    for (i = v.begin(); i < v.end()-1; i++)
    {
        for (j = i + 1; j < v.end(); j++)
        { // 检查是否存在与 i 和 j 在x或y坐标上对应的点，确认是否可以形成矩形的对角线
            if (binary_search(v.begin(), v.end(), Point(j->x, i->y)) &&
				binary_search(v.begin(), v.end(), Point(i->x, j->y)) &&
                // 确保 i 和 j 不在同一行或同一列
                // 检查2个点是否与x或y坐标线平行，通过以下4个条件隐含完成
				i->x != j->x &&
				i->y != j->y ){
                    nTotalNum++; // 找到一个矩形, +1;
                }
        }
    }
    
    cout << nTotalNum / 2 << endl; // 每个矩形被计数两次，所以结果要除以2

    return 0;
}