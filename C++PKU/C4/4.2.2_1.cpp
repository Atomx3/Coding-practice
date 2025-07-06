/*
编程题＃2：拨钟问题

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述：有9个时钟，排成一个3*3的矩阵。(图 1)

        |-------|    |-------|    |-------|
        |       |    |       |    |   |   |
        |---O   |    |---O   |    |   O   |
        |       |    |       |    |       |
        |-------|    |-------|    |-------|    
            A            B            C    
        |-------|    |-------|    |-------|
        |       |    |       |    |       |
        |   O   |    |   O   |    |   O   |
        |   |   |    |   |   |    |   |   |
        |-------|    |-------|    |-------|    
            D            E            F    
        |-------|    |-------|    |-------|
        |       |    |       |    |       |
        |   O   |    |   O---|    |   O   |
        |   |   |    |       |    |   |   |
        |-------|    |-------|    |-------|    
            G            H            I    
                       
现在需要用最少的移动，将9个时钟的指针都拨到12点的位置。共允许有9种不同的移动。
如下表所示，每个移动会将若干个时钟的指针沿顺时针方向拨动90度。


(图 2)：
移动    影响的时钟  
 1        ABDE 
 2        ABC 
 3        BCEF 
 4        ADG 
 5        BDEFH 
 6        CFI 
 7        DEGH 
 8        GHI 
 9        EFHI         

输入：
从标准输入设备读入9个整数，表示各时钟指针的起始位置。0=12点、1=3点、2=6点、3=9点。

输出：
输出一个最短的移动序列，使得9个时钟的指针都指向12点。按照移动的序号大小，输出结果。

样例输入：
3 3 0
2 2 2
2 1 2

样例输出：
4 5 8 9 


根据题目描述，如下解释是正确的吗？：
1. 时钟序号和字母编号的对应关系为：按照序号1-9依次对应A-I，例如B（2）、D（4）、F（6）、H（8）。

2. 每个钟移动时，会顺带将其周围若干个时钟也拨动，每次指针沿顺时针方向拨动90度，例如

拨动时钟A（1），同时影响：A、B、D、E。
拨动时钟B（2），同时影响：A、B、C。

以此类推。。

但是，为何B（2）、D（4）、F（6）、H（8）只同时影响相邻的2个时钟？而其他时钟却能影响与其相邻的更多时钟？

影响范围的差异确实是题目设置的特殊规则，人为定义的移动组合，非基于时钟的物理相邻关系。
这种设计增加了问题的复杂度，需要更复杂的解法。

以下解法符合c++98标准。

*/

#include <iostream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

// 定义9种移动影响的时钟组合
const int moves[9][9] = {
    {1,1,0,1,1,0,0,0,0}, // 移动1: ABDE
    {1,1,1,0,0,0,0,0,0}, // 移动2: ABC
    {0,1,1,0,1,1,0,0,0}, // 移动3: BCEF
    {1,0,0,1,0,0,1,0,0}, // 移动4: ADG
    {0,1,0,1,1,1,0,1,0}, // 移动5: BDEFH
    {0,0,1,0,0,1,0,0,1}, // 移动6: CFI
    {0,0,0,1,1,0,1,1,0}, // 移动7: DEGH
    {0,0,0,0,0,0,1,1,1}, // 移动8: GHI
    {0,0,0,0,1,1,0,1,1}  // 移动9: EFHI
};

// 检查当前时钟状态是否全部为0(12点)
bool checkClocks(const int clocks[9]) {
    for (int i = 0; i < 9; ++i) {
        if (clocks[i] != 0) return false;
    }
    return true;
}

// 执行移动操作
void applyMove(int clocks[9], int move, int times) {
    for (int i = 0; i < 9; ++i) {
        if (moves[move][i]) {
            clocks[i] = (clocks[i] + times) % 4;
        }
    }
}

// 枚举所有可能的移动组合
vector<int> solveClocks(int clocks[9]) {
    vector<int> bestSolution;
    int minSteps = INT_MAX;
    
    // 枚举每种移动的执行次数(0-3次)
    for (int m1 = 0; m1 < 4; ++m1) {
        for (int m2 = 0; m2 < 4; ++m2) {
            for (int m3 = 0; m3 < 4; ++m3) {
                for (int m4 = 0; m4 < 4; ++m4) {
                    for (int m5 = 0; m5 < 4; ++m5) {
                        for (int m6 = 0; m6 < 4; ++m6) {
                            for (int m7 = 0; m7 < 4; ++m7) {
                                for (int m8 = 0; m8 < 4; ++m8) {
                                    for (int m9 = 0; m9 < 4; ++m9) {
                                        int tempClocks[9];
                                        memcpy(tempClocks, clocks, sizeof(tempClocks));
                                        
                                        applyMove(tempClocks, 0, m1);
                                        applyMove(tempClocks, 1, m2);
                                        applyMove(tempClocks, 2, m3);
                                        applyMove(tempClocks, 3, m4);
                                        applyMove(tempClocks, 4, m5);
                                        applyMove(tempClocks, 5, m6);
                                        applyMove(tempClocks, 6, m7);
                                        applyMove(tempClocks, 7, m8);
                                        applyMove(tempClocks, 8, m9);
                                        
                                        if (checkClocks(tempClocks)) {
                                            int totalSteps = m1 + m2 + m3 + m4 + m5 + m6 + m7 + m8 + m9;
                                            if (totalSteps < minSteps) {
                                                minSteps = totalSteps;
                                                bestSolution.clear();
                                                if (m1 > 0) bestSolution.insert(bestSolution.end(), m1, 1);
                                                if (m2 > 0) bestSolution.insert(bestSolution.end(), m2, 2);
                                                if (m3 > 0) bestSolution.insert(bestSolution.end(), m3, 3);
                                                if (m4 > 0) bestSolution.insert(bestSolution.end(), m4, 4);
                                                if (m5 > 0) bestSolution.insert(bestSolution.end(), m5, 5);
                                                if (m6 > 0) bestSolution.insert(bestSolution.end(), m6, 6);
                                                if (m7 > 0) bestSolution.insert(bestSolution.end(), m7, 7);
                                                if (m8 > 0) bestSolution.insert(bestSolution.end(), m8, 8);
                                                if (m9 > 0) bestSolution.insert(bestSolution.end(), m9, 9);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return bestSolution;
}

int main() {
    int clocks[9];
    
    // 读取输入
    for (int i = 0; i < 9; ++i) {
        cin >> clocks[i];
    }
    
    // 解决问题
    vector<int> solution = solveClocks(clocks);
    
    // 输出结果
    for (size_t i = 0; i < solution.size(); ++i) {
        if (i != 0) cout << " ";
        cout << solution[i];
    }
    cout << endl;
    
    return 0;
}