
/*
4. 算法基础
2. 第2 module
2. 编程题＃2：连坐灯开关

输入：
第一行是一个正整数N, 表示需要解决的案例组数；
每组案例由5X6的矩阵组成，其中每个元素为一盏灯，并具有初始状态0或1；
0 表示灯的初始状态是熄灭的；
1 表示灯的初始状态是点亮的；

求解决方案：开关灯的规则为，每按下一个灯的开关，
将会同时影响周围的几个灯的状态向相反的状态变化；
按下多少个灯（1），可以关闭全部的灯（0）？

输出：
按照该案例5X6的矩阵格式输出
• 1 表示需要把对应的按钮按下
• 0 表示不需要按对应的按钮

0 1 1 0 1 0
1 0 0 1 1 1
0 0 1 0 0 1
1 0 0 1 0 1
0 1 1 1 0 0
PUZZLE #1
1 0 1 0 0 1 
1 1 0 1 0 1 
0 0 1 0 1 1 
1 0 0 1 0 0 
0 1 0 0 0 0 

0 0 1 0 1 0
1 0 1 0 1 1
0 0 1 0 1 1
1 0 1 1 0 0
0 1 0 1 0 0 
PUZZLE #2
1 0 0 1 1 1 
1 1 0 0 0 0 
0 0 0 1 0 0 
1 1 0 1 0 1 
1 0 1 1 0 1 

语句解释：while(success == false){ }
press 矩阵的第一行被枚举，为找到一个能够关闭所有灯的配置。
一旦 guess() 函数返回 true，循环就会结束，
此时 press 矩阵中存储的就是正确的配置。
*/

#include <stdio.h>
// puzzle 数组存储了每个案例的初始灯泡状态;
// press 数组则用于存储需要按下哪些开关来关闭所有灯泡;
int puzzle[6][8], press[6][8];

/*guess() 函数的作用是根据 press 数组的第一行和 
puzzle 数组计算出 press 数组的其他行。*/
bool guess(){
    int c, r;
    // 根据press第1行和puzzle数组, 计算press其他行的值
    for(r=1; r<5; r++){
        for(c=1; c<7; c++){
            press[r+1][c] = (puzzle[r][c]+press[r][c]+
            press[r-1][c]+ press[r][c-1]+press[r][c+1]) %2;
        }
    }
    // 判断所计算的press数组能否熄灭第5行的所有灯
    for(c=1; c<7; c++){
        if ((press[5][c-1] + press[5][c] + press[5][c+1] +
            press[4][c]) %2 != puzzle[5][c] ){
            return(false);// false 表示不能关闭
        }
    }
    return(true);// true 表示成功关闭最后一行灯
}

void enumerate (){
    int c;
    bool success;
    for ( c=1; c<7; c++){
        press[1][c] = 0;
    }
    // 将枚举的值传给 guess 函数来判断真假
    success = guess();
    while(success == false){
        press[1][1]++;
        c = 1;
        // 对第1行的元素press[1][c]的枚举赋值0或1
        while (press[1][c] > 1) {
            press[1][c] = 0;
            c++;
            press[1][c]++;
        }
        success = guess(); // 更新 success 变量的值
    }
    return;
}

int main() {
    int cases, i, r, c;
    scanf("%d", &cases);// 输入数量为cases组的数据
    for ( r=0; r<6; r++ )
    // 设置0和7列=0，实际仅仅计算[5][6]矩阵；
        press[r][0] = press[r][7] = 0;
    for ( c=1; r<7; r++ )
        press[0][c] = 0; // 设置0行=0；
    for (i=0; i<cases; i++){
        for(r=1; r<6; r++)
            for(c=1; c<7; c++)
            // 输入灯的初始状态到puzzle[5][6]矩阵
                scanf("%d", &puzzle[r][c]);
        enumerate ();// 枚举 press[r][c]=1或0并返回真假；
        printf("PUZZLE #%d\n", i+1);
        for(r=1; r<6; r++){
            for(c=1; c<7; c++)
                printf("%d ", press[r][c]);
            printf("\n");
        }
    }
    return 0; 
}
