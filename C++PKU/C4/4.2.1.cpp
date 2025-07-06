/*
4. 算法基础
2. module 2
1. 编程题＃1： 画家问题（熄灯开关问题的变种）

按照c++98的标准，写一个c++程序，解决以下问题：

描述：
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。
Bob是个画家，想把全部的砖都涂成黄色。但他的画笔不好使。当他用画笔涂画第(i, j)个位置的砖时， 
位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)上的砖都会改变颜色。
请你帮助Bob计算出最少需要涂画多少块砖，才能使所有砖的颜色都变成黄色（颜色可逆）。

输入：
第一行是个整数t(1≤t ≤20)，表示要测试的案例数。然后是t个案例。
每个案例的首行是一个整数n (1≤n ≤15)，表示墙的大小。
接下来的n行表示墙的初始状态。每一行包含n个字符。
第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。

输出：
每个案例输出一行。如果Bob能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数，否则输出“inf”。


案例输入：
2
3
yyy
yyy
yyy
5
wwwww
wwwww
wwwww
wwwww
wwwww

案例输入数据说明：
首行输入2，表示有两组测试数据。
然后，输入整数3，表示第一个案例的N为3。
然后，下方为第一个案例的N*N的砖头矩阵，其中的元素为初始状态的砖头颜色，
由字符y或w表示，字符中间无空格，砖头的黄色用字符y表示，白色用w表示。

案例输出
0
15 

案例输出数据说明：
第一个案例中，所有的砖都是黄色的，因此不需要涂画任何砖，输出0。
第二个案例中，所有的砖都是白色的，Bob需要涂画所有的砖，输出15。
至少涂15块砖可以将以上的25块砖都变成黄色。
如果不能将所有的砖都涂成黄色，则输出“inf”

特别说明：该题是经典的"熄灯问题"(Lights Out)变种，
按第二次，开关恢复到原来状态，墙面颜色是可逆的。
所以，对于有限的整数N，可能会输出inf的无解答案。

*/

#include <iostream>
#include <cstring>
using namespace std;

// 定义墙面和涂色状态的二维数组，大小为17x17（15+2边界）
int wall[17][17], paint[17][17];
int width;      // 墙面实际宽度
int minCount;   // 最小涂色次数

// 计算当前涂色方案的总涂色次数
int Count()
{
    int sum = 0;
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= width; j++)
            sum += paint[i][j];
    return sum;
}

// 初始化墙面状态
void init()
{
    memset(wall, 0, sizeof(wall));
    memset(paint, 0, sizeof(paint));
    
    // 读取输入数据，'w'表示白色(1)，'y'表示黄色(0)
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= width; j++) {
            char tmp;
            cin >> tmp;
            wall[i][j] = (tmp == 'w') ? 1 : 0;
        }
}

// 检查最后一行是否符合要求
bool guess()
{
    for (int j = 1; j <= width; j++)
        // 检查当前格子是否可以通过涂色满足要求
        if ((paint[width][j-1] + paint[width][j] + paint[width][j+1] + paint[width-1][j]) % 2 != wall[width][j])
            return false;
    return true;
}

// 根据第一行的涂色方案推导其他行的涂色方案
void update()
{
    for (int i = 1; i < width; i++)
        for (int j = 1; j <= width; j++)
            // 根据上一行和相邻格子的状态决定当前格子是否需要涂色
            paint[i+1][j] = (wall[i][j] + paint[i][j] + paint[i][j-1] + paint[i][j+1] + paint[i-1][j]) % 2;
}

// 枚举所有可能的第一行涂色方案
void enumerate()
{
    // 遍历所有可能的涂色组合(2^width种)
    for (int i = 0; i < (1 << width); i++) {
        memset(paint, 0, sizeof(paint));
        
        // 设置第一行的涂色方案
        for (int j = 0; j < width; j++)
            paint[1][width-j] = (i >> j) & 1;
        
        // 推导其他行的涂色方案并检查是否有效
        update();
        if (guess()) {
            int cnt = Count();
            if (cnt < minCount)
                minCount = cnt;
        }
    }
}

int main()
{
    int ncase;
    cin >> ncase;  // 读取测试用例数量
    
    while (ncase--) {
        cin >> width;
        minCount = width * width + 1;  // 初始化最小次数为不可能的大值
        init();     // 初始化墙面
        enumerate(); // 枚举所有涂色方案
        
        // 输出结果
        if (minCount == width * width + 1)
            cout << "inf" << endl;  // 无解情况
        else
            cout << minCount << endl; // 输出最小涂色次数
    }
    return 0;
}
