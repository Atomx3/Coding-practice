/*
1. 计算导论与C语言基础，系列第1课  
8. 理性认识C程序 导论，第8周  
2.5 编程题＃5：自整除数

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
对一个整数n,如果其各个位数的数字相加得到的数m能整除n,
则称n为自整除数.例如21,21%(2+1)==0,所以21是自整除数.
现求出从10到n(n < 100)之间的所有自整除数.

输入
有一行,整数n,(10 <= n < 100)

输出
有多行.按从小到大的顺序输出所有大于等于10,小于等于n的自整除数,每行一个自整除数.

样例输入
47

样例输出
10
12
18
20
21
24
27
30
36
40
42
45



*/

#include <iostream>
using namespace std;
int main(){
/*
对一个整数n,如果其各个位数的数字相加得到的数m能整除n,
则称n为自整除数.例如21,21%(2+1)==0,所以21是自整除数.
现求出从10到n(n < 100)之间的所有自整除数.
*/

int n=0, m=0;
cin>>n;

// find all i
for(int i=10; i<=n; i++){
    m=i/10+i%10;
    if(i%m==0){
        cout<<i<<endl;
    }
    
    
}
    

	return 0;
}