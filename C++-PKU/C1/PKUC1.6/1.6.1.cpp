/*
1. 计算导论与C语言基础，系列第1课
6. 理性认识C程序 导论，第6周
1. 编程题 ＃1：细菌实验分组
*/

#include <iostream>
using namespace std;

int main() {
    // input numbers on each line count by i;
    int n, id[100], a1, a2, i;
    double rate[100];
    cin >> n;

    for(i=0; i<n; i++){
        cin >> id[i] >> a1 >>a2;
        rate[i]=(double)a2/a1;
    }

    // order by growing.
    for (int i=0; i<n; i++){
        for (int j=0; j<n-i-1; j++){
            if(rate[j]>rate[j+1]){
            int tempId= id[j];
            id[j]=id[j+1];
            id[j+1]=tempId;
            double tempRate= rate[j];
            rate[j]=rate[j+1];
            rate[j+1]=tempRate;
            }
        }
    }

    // record the max.
    double maxDiff;
    int maxDiffIndex;
    for (int i=0; i<n-1; i++){
        double diff = rate[i+1]-rate[i];
        if(diff>maxDiff){
            maxDiff=diff;
            maxDiffIndex=i;
        }
    }
    
    // output the max.
    cout<< n-maxDiffIndex-1 <<endl;
    for (int i=maxDiffIndex+1; i< n; i++){
        cout<< id[i] << endl;
    }

    // ouput the min.
    cout<< maxDiffIndex+1 <<endl;
    for(int i=0; i<maxDiffIndex+1; i++)
    {
        cout<< id[i] <<endl;
    }

    

    return 0;
}
//why i-- ? how is the increment algorithms here?