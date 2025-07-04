/*
3. C程序设计进阶
9. 第8 module
6. 编程题＃6： priority queue练习题
container

应满足以下条件：
1. 优先级最高的整数：
质因数数目（不包括自身）最多；
*当多个整数的质因数数目相等时，数值较大者优先级高。
例如66,30,100，计算结果，其质因数分别为
66：11, 2, 3（3个-不同质因数）；
30：3, 2, 5 （3个-不同质因数）；
100: 2, 5 (2个- 不同质因数)；
100 比较其他两者为更小优先级；
同级别（3个）比较，66优先级高于30，因此66优先级最高；

2. 优先级最低的整数：
质因数数目（不包括自身）最少；
*当多个整数的质因数数目相等时，数值较小者优先级最低。
例如4，8，9，计算结果，其质因数均为1；
幂次分别为2，3，2，同级别比较，4优先级最低，9最高；

3. 对于质因数为自身的数字，应该减去1。
例如5，7 计算结果，其质因数均为1，但在本例题中为0；

*/
#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>
using namespace std;

// 函数来计算一个数的质因数个数（不包括自身）
int countPrimeFactors(int n) {
    if (n < 2) return 0; // 小于2的数没有质因数
    int count = 0;
    if (n % 2 == 0) {
        count++;
        while (n % 2 == 0) n /= 2;
    }
    for (int i = 3; i <= sqrt(n); i += 2) {
        if (n % i == 0) {
            count++;
            while (n % i == 0) n /= i;
        }
    }
    // 如果n是大于2的质数，则减去1，因为质因数为自身
    if (n > 2) count++;
    return count - (n != 1 && count == 1 ? 1 : 0);
}

// 比较函数，用于最大优先队列
struct CompareMax {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return a.second < b.second; // 当质因数个数相等时，数值大的优先
        return a.first < b.first; // 质因数个数多的优先
    }
};

// 比较函数，用于最小优先队列
struct CompareMin {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return a.second > b.second; // 当质因数个数相等时，数值小的优先
        return a.first > b.first; // 质因数个数少的优先
    }
};

int main() {
    int num;
    cin >> num; // 读取添加元素的次数

    while (num--) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareMax> pq_max; // 创建最大优先队列
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareMin> pq_min; // 创建最小优先队列

        for (int i = 0; i < 10; ++i) {
            int element;
            cin >> element; // 读取元素
            int factors = countPrimeFactors(element);
            pq_max.push({factors, element}); // 将元素及其质因数个数添加到最大优先队列中
            pq_min.push({factors, element}); // 将元素及其质因数个数添加到最小优先队列中
        }

        // 输出优先级最高的整数
        cout << pq_max.top().second << " ";
        pq_max.pop();

        // 输出优先级最低的整数
        cout << pq_min.top().second << endl;
        pq_min.pop();
    }

    return 0;
}
