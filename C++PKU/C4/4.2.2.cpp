/*
4. 算法基础
2. 第2 module
2. 编程题＃2：拨钟问题
原题没看懂，CS专业的人似乎自然语言都没学好，经常讲一些让人看不懂的话。

// 定义时钟拼图问题的解决方案
例如，操作A：影响时钟 1, 2, 4。每次执行都会使这些时钟顺时针转动90度，依次类推。
A: 1 2 4
B: 1 2 3 5 
C: 2 3 6
D: 1 4 5 7
E: 1 3 5 7 9
F: 3 5 6 9
G: 4 7 8
H: 5 7 8 9
I: 6 8 9
*/ 

#include <iostream>
#include <numeric>
using namespace std;

// 初始化时钟数组和操作次数数组
int Clock[10] = { 0 };
int tic[10] = { 0 };
// 初始化最小步骤数为一个很大的数
int minStep = 1000000;
// 初始化记录最小步骤的数组
int minTic[10] = { 0 };

// 更新tic数组的函数，根据tic[1]、tic[2]、tic[3]的值来计算其他操作的必要次数
void update()
{
    // 根据当前时钟状态和已经执行的操作来计算剩余操作的必要次数
    tic[4] = (4 - (Clock[1] + tic[1] + tic[2]) % 4) % 4;
    tic[5] = (4 - (Clock[2] + tic[1] + tic[2] + tic[3]) % 4) % 4;
    tic[6] = (4 - (Clock[3] + tic[2] + tic[3]) % 4) % 4;
    tic[7] = (4 - (Clock[4] + tic[1] + tic[4] + tic[5]) % 4) % 4;
    tic[9] = (4 - (Clock[5] + tic[1] + tic[3] + tic[5] + tic[7]) % 4) % 4;
    tic[8] = (4 - (Clock[7] + tic[4] + tic[7]) % 4) % 4;
}

// 检查所有时钟是否都指向12点的函数
bool check()
{
    // 如果任何一个检查失败，返回false
    if ((Clock[6] + tic[3] + tic[5] + tic[6] + tic[9]) % 4)
    {
        return false;
    }
    if ((Clock[8] + tic[5] + tic[7] + tic[8] + tic[9]) % 4)
    {
        return false;
    }
    if ((Clock[9] + tic[6] + tic[8] + tic[9]) % 4)
    {
        return false;
    }
    // 如果所有检查都通过，返回true
    return true;
}

// 枚举所有可能的操作组合的函数
void enumerate()
{
    // 遍历tic[1]、tic[2]、tic[3]的所有可能值
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                tic[1] = i; // 设置操作A的次数
                tic[2] = j; // 设置操作B的次数
                tic[3] = k; // 设置操作C的次数
                update();   // 更新剩余操作的必要次数
                if (check()) // 检查是否所有时钟都指向12点
                {
                    // 计算当前组合的总操作次数
                    int tmp = accumulate(tic, tic + 10, 0);
                    // 如果当前组合的操作次数小于已知的最小步骤数
                    if (tmp < minStep)
                    {
                        // 更新最小步骤数和对应的操作次数
                        minStep = tmp;
                        for (int i = 0; i < 10; i++)
                        {
                            minTic[i] = tic[i];
                        }
                    }
                }
            }
        }
    }
}

// 主函数
int main()
{
    // 读取时钟的初始位置
    for (int i = 1; i <= 9; i++)
    {
        cin >> Clock[i];
    }
    enumerate(); // 执行枚举函数，找到解决方案
    // 输出解决方案，即每个操作需要执行的次数
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 0; j < minTic[i]; j++)
        {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}
