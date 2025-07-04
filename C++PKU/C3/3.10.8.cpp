/*
3. C程序设计进阶
10. 第10 module
8. 编程题＃8：计算整数k

二进制、十进制、十六进制位操作
~n 取反
& 与运算符
｜或运算符
<< 左移运算符
>> 右移运算符
^  异或运算符
1u 无符号整数1
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int t;
    cin >> t; // 读取数据组数
    while (t--) {
        unsigned int n, i, j;
        cin >> n >> i >> j; // 读取n, i, j

        // 创建掩码，将i到j-1之间的所有位设置为1
        unsigned int mask = ((1u << (j - i - 1)) - 1) << (i + 1);

        // 将第j位设置为与n相反的值
        // ~n是n的位反转，(~n >> j) 将n的第j位移动到最低位
        mask |= ((~n >> j) & 1u) << j;

        // 将第i位设置为与n相同的值，只在第i位有1的数，然后与n进行与操作，
        // 确保只有第i位被考虑。然后，这个值通过或操作被添加到掩码中。
        mask |= (n & (1u << i));

        // 按十六进制输出结果，不使用0x前缀
        cout << hex << mask << endl;
    }
    return 0;
}
