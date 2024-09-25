/*
4. 算法基础
2. 第2周
1. 编程题＃1：百钱百鸡问题
• 鸡翁一值钱五, 鸡母一值钱三, 鸡雏三值钱一.
百钱买百鸡, 问鸡翁, 鸡母, 鸡雏各几何
—— 张丘建《算经》
*/

#include <iostream>
using namespace std;

int main() {
    // 公鸡、母鸡、小鸡的数量
    int rooster, hen, chick;
    
    // 枚举公鸡和母鸡的数量
    for(rooster = 0; rooster <= 100/5; ++rooster) {
        for(hen = 0; hen <= (100-rooster)/3; ++hen) {
            chick = 100 - rooster - hen;
            
            // 检查当前组合是否满足条件
            if((rooster * 5 + hen * 3 + chick / 3 == 100) && (chick % 3 == 0)) {
                cout << "公鸡: " << rooster << " 只, "
                     << "母鸡: " << hen << " 只, "
                     << "小鸡: " << chick << " 只" << endl;
            }
        }
    }
    
    return 0;
}
