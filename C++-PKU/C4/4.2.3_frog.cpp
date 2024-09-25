/*
4. 算法基础
2. 第2周
3. 编程题＃：青蛙踩稻秧

这个问题通常涉及到一个矩形稻田，其中青蛙会跳过稻田并踩坏稻子。
目标是找到一条路径，使得这条路径上被踩坏的稻子数量最多。

eg 输入数据
6 7
14
2 1 
6 6 
4 2 
2 5
2 6
2 7
3 4
6 1
6 2
2 3
6 3
6 4
6 5
6 7

eg 输出数据 7

解释：
sort是STL内置标准函数，operator< 也是可以直接调用，处理通用的算法；
此案例中，需要对自定义类型（如 Plant 结构体）进行排序，
因此operator<重载，也就是被重写，重新定义了规则，为了满足特定的案例的算法需求。

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Plant {
    int x, y;// 植物在网格中的坐标
};
// 配合 sort 函数对植物进行排序
bool operator<(const Plant& a, const Plant& b) {
    // 如果两个 Plant 对象的 x 坐标相同，那么将根据 y 坐标进行排序
    if (a.x == b.x) return a.y < b.y;
    // 如果 x 坐标不同，那么它们将根据 x 坐标进行排序
    return a.x < b.x;
}

int main() {
    int R, C, N;
    cin >> R >> C >> N;
    vector<Plant> plants(N);
    // 植物坐标存储到 plants 向量的每个植物对象的x和y成员变量中
    for (int i = 0; i < N; ++i) {
        cin >> plants[i].x >> plants[i].y;
    }
    // sort 函数对 plants 向量按先x（后y）坐标进行升序排列，以便后续操作。
    sort(plants.begin(), plants.end());

    int maxPlants = 0;// 存储最长序列的长度
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            // 计算同一行的两棵植物之间的列宽度
            int dx = plants[j].x - plants[i].x;
             // 计算同一列的两棵植物之间的行宽度
            int dy = plants[j].y - plants[i].y;
            // 假设植物的起始坐标点
            int prevX = plants[i].x - dx;
            int prevY = plants[i].y - dy;
            // 验证起始坐标点是否在网格的有效范围内，否则continue跳过，寻找下一个可能的植物序列
            if (prevX <= 0 || prevY <= 0 || prevY > C || prevX > R) continue;
            //定义同一个序列的 x，y 值，至少2株植物已在
            int count = 2;
            int x = plants[j].x + dx;
            int y = plants[j].y + dy;
            // binary_search 函数检查序列中的下一个植物是否存在于 plants 向量中。
            while (x <= R && y <= C && binary_search(plants.begin(), plants.end(), Plant{x, y})) {
                x += dx;
                y += dy;
                ++count;
            }
            // 比较 maxPlants 和 count 的值，返回两者之间的较大值。
            maxPlants = max(maxPlants, count);
        }
    }
    // 有效序列至少需要包含3株植物
    if (maxPlants < 3) maxPlants = 0;
    else maxPlants += 1; // 加上起始点
    cout << maxPlants << endl;
    return 0;
}

