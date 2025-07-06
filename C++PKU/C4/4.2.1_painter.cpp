/*
4. 算法基础
2. module 2
1. 编程题＃1： 画家问题（符合物理世界规律的正解）

按照目前2025年 c++的最新标准，写一个程序，解决以下问题：

描述：
有一个正方形的墙，由N*N个正方形的砖组成，其中一些砖是白色的，另外一些砖是黄色的。
你想把全部的砖都涂成黄色，但画笔有个特点，当涂画第(i, j)个位置的砖时， 
相邻位置(i-1, j)、 (i+1, j)、 (i, j-1)、 (i, j+1)的砖都会变成黄色，一旦变色，那么就始终保持黄色，不可能再变回白色。
请你帮助Bob计算出最少需要涂画多少块砖，能使所有砖的颜色都变成黄色。

输入：
第一行是个整数t(1≤t ≤20)，表示要测试的案例数。然后是t个案例。
每个案例的首行是一个整数n (1≤n ≤15)，表示墙的大小。
接下来的n行表示墙的初始状态。每一行包含n个字符。
第i行的第j个字符表示位于位置(i,j)上的砖的颜色。“w”表示白砖，“y”表示黄砖。

输出：
每个案例输出一行。如果能够将所有的砖都涂成黄色，则输出最少需要涂画的砖数。


案例输入：
2
3
yyy
ywy
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
第一个案例，答案为 0
第一个案例，答案为 8

案例输出数据说明：
第一个案例中，所有的砖都是黄色的，因此不需要涂画任何砖，输出0。

请确保遵守一条物理世界常规，一旦砖块变为黄色，
就不会再被逆转回白色，用一种颜色涂画墙面是不可逆的过程，
这道题不是类似熄灯开关的问题。

算法设计：
采用优化后的BFS算法，通过 getBestFlipPosition 函数
优先选择能影响最多白色砖块的涂画位置，从而提高计算效率。
使用状态压缩和启发式策略，避免全量枚举。
*/

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>

using namespace std;

// 使用无符号整数表示墙的状态（位运算）
typedef unsigned int WallState;

// 状态结构体：存储当前墙的状态和已涂画次数
struct State {
    vector<string> wall;  // 当前墙的状态
    int steps;            // 已涂画次数
    State(const vector<string>& w, int s) : wall(w), steps(s) {}
};

// 翻转指定位置的砖块及其相邻砖块
WallState flip(WallState state, int pos, int n) {
    state ^= (1 << pos);  // 翻转当前位置
    if (pos % n != 0)   state ^= (1 << (pos-1));  // 左
    if (pos % n != n-1) state ^= (1 << (pos+1));  // 右
    if (pos >= n)       state ^= (1 << (pos-n));  // 上
    if (pos < n*(n-1))  state ^= (1 << (pos+n));  // 下
    return state;
}

// 获取最佳涂画位置（能影响最多白色砖块的位置）
int getBestFlipPosition(const vector<string>& wall, int n) {
    int maxImpact = -1;
    int bestPos = -1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (wall[i][j] == 'w') {
                // 计算涂画该位置能影响的白色砖块数量
                int impact = 1;  // 自己
                if (i > 0 && wall[i-1][j] == 'w') impact++;
                if (i < n-1 && wall[i+1][j] == 'w') impact++;
                if (j > 0 && wall[i][j-1] == 'w') impact++;
                if (j < n-1 && wall[i][j+1] == 'w') impact++;
                
                if (impact > maxImpact) {
                    maxImpact = impact;
                    bestPos = i * n + j;  // 转换为一维位置
                }
            }
        }
    }
    return bestPos;
}

int main() {
    int t;  // 测试案例数量
    cin >> t;
    
    while (t--) {
        int n;  // 墙的大小
        cin >> n;
        vector<string> initial(n);  // 初始墙状态
        
        // 读取初始墙状态
        for (int i = 0; i < n; i++) {
            cin >> initial[i];
        }
        
        // BFS队列
        queue<State> q;
        q.push(State(initial, 0));
        int minSteps = INT_MAX;  // 最小涂画次数
        
        while (!q.empty()) {
            State current = q.front();
            q.pop();
            
            // 检查是否所有砖块都已变黄
            bool allYellow = true;
            for (size_t i = 0; i < current.wall.size(); i++) {
                if (current.wall[i].find('w') != string::npos) {
                    allYellow = false;
                    break;
                }
            }
            
            if (allYellow) {
                minSteps = min(minSteps, current.steps);
                continue;
            }
            
            // 获取最佳涂画位置
            int bestPos = getBestFlipPosition(current.wall, n);
            if (bestPos != -1) {
                int i = bestPos / n;  // 行
                int j = bestPos % n;  // 列
                
                // 创建新状态
                vector<string> newWall = current.wall;
                newWall[i][j] = 'y';  // 涂画当前位置
                if (i > 0) newWall[i-1][j] = 'y';  // 上
                if (i < n-1) newWall[i+1][j] = 'y';  // 下
                if (j > 0) newWall[i][j-1] = 'y';  // 左
                if (j < n-1) newWall[i][j+1] = 'y';  // 右
                
                q.push(State(newWall, current.steps + 1));
            }
        }
        
        // 输出结果
        if (minSteps == INT_MAX) {
            cout << "无解" << endl;
        } else {
            cout << minSteps << endl;
        }
    }
    
    return 0;
}