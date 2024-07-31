/*
A、B、C三根柱子在递归过程中的角色（source, target, auxiliary）是会变化的。
我们需要将不同的柱子作为源柱子（source）、目标柱子（target）和辅助柱子（auxiliary）来解决子问题
輸入一個比較小的數，例如 3
*/
#include <iostream>
using namespace std;

// 汉诺塔递归函数
void hanoi(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        cout << "Move disk 1 from " << source << " to " << target << endl;
        return;
    }
    // 将n-1个圆盘从源柱移动到辅助柱，此时辅助柱子暂时充当目标柱子的角色。
    // 移动最大的圆盘（第n个圆盘）到目标柱子
    hanoi(n - 1, source, auxiliary, target);
    cout << "Move disk " << n << " from " << source << " to " << target << endl;
    // 辅助柱子变成了新的源柱，目标柱保持不变，原来的源柱子现在变成辅助柱子。
    hanoi(n - 1, auxiliary, target, source);
}

int main() {
    int numDisks;
    cout << "Enter the number of disks: ";
    cin >> numDisks;

    hanoi(numDisks, 'A', 'C', 'B'); // A、B、C 分别表示三根柱子

    return 0;
}
