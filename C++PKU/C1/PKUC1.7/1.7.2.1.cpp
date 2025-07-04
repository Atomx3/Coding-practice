/*
1. 计算导论与C语言基础，系列第1课  
7. 理性认识C程序 导论，第7 module  
2.1 编程题＃1：年龄与疾病

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
某医院想统计一下某项疾病的获得与否与年龄是否有关，需要对以前的诊断记录进行整理。

输入
共2行，第一行为过往病人的数目n（0 < n <= 100)，第二行为每个病人患病时的年龄。

输出
每个年龄段（分四段：18以下，19-35，36-60，大于60注意看样例输出的格式）的患病人数占总患病人数的比例，以百分比的形式输出，精确到小数点后两位（double）。关于c++的格式化的输入输出，请参考：http://www.cplusplus.com/reference/iomanip。也可以在网上搜索一下，资料很多的。

样例输入
10
1 11 21 31 41 51 61 71 81 91

样例输出
1-18: 20.00%
19-35: 20.00%
36-60: 20.00%
60-: 40.00%

提示
注意最后一行的输出是“60-: ”，而不是“61-: ”。

每个冒号之后有一个空格。

输出可以用 cout<<fixed<<setprecision(2) << f; 来保留f后面的两位小数。

*/

#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    // input patients number n
    int n=0;
    cin>>n;

    // input the patients age into array
    int age[n];
    for(int i=0; i<n; i++){
        cin>>age[i]; 
    }

    // count the numbers of each age group;
    int age18l =0, age35l=0, age60l=0, age60m=0;
    for(int i=0; i<n; i++){

        if(age[i] <=18 ){ age18l ++;}
        else if(age[i]>=19 && age[i]<=35){age35l++;}
        else if (age[i]>=36 && age[i]<=60){age60l++;}
        else {age60m ++;}
        
        }
    
    double age18lr= (double)age18l/n *100 ;
    double age35lr= (double)age35l/n *100 ;
    double age60lr= (double)age60l/n *100 ;
    double age60mr= (double)age60m/n *100;
    
    // output the rate of each age group.
    // std::cout<<"1-18:"<< std::fixed<< std::setprecision(2)<<age18lr<<"%"<<std::endl;
    // printf("1-18: %.2f %%\n",age18lr);  
    // printf("19-35: %.2f %%\n",age35lr);  
    // printf("36-60: %.2f %%\n",age60lr);  
    // printf("60-: %.2f %%\n",age60mr);

    cout<<"1-18: "<<fixed<<setprecision(2) << age18lr<<"%"<<endl;   
    cout<<"19-35: "<<fixed<<setprecision(2) << age35lr<<"%"<<endl;   
    cout<<"36-60: "<<fixed<<setprecision(2) << age60lr<<"%"<<endl;   
    cout<<"60-: "<<fixed<<setprecision(2) << age60mr<<"%"<<endl;   


    return 0;
    }
    

   