#include <iostream>
#include <iomanip>

using namespace std;

/*
编程题＃5：细菌实验分组
类似于 1.10.5，编程题＃5：异常细胞检测
*/


void rate_sort(int n, int id[100], double rate[100]){
    
    // sort rate[] array in Ascending Order
    // bubble sorting algorithm for two parallel array in the same time.
        int temp_id=0;
        double temp_rate=0;
        for(int i=0; i<n; i++){
            for(int j=0;j<n-1;j++){
                if(rate[j]>rate[j+1]){
                temp_id=id[j];
                id[j]=id[j+1];
                id[j+1]=temp_id;
                temp_rate=rate[j];   
                rate[j]=rate[j+1];
                rate[j+1]=temp_rate; 
                }
            }
        }
    /*
    // output the sorted array.
        for(int i=0; i<n; i++){
        cout<<id[i]<<setw(7)<<rate[i]<<endl;} 
    */
    // find the max Difference.
    int index=0;
    double temp_max=0;
    for(int i=0; i<n;i++){
        double maxDiff= rate[i+1]-rate[i];
        if(temp_max<maxDiff){
            temp_max=maxDiff;
            index=i;
        }
    }
    //seperate the group A strong bacteria.
    cout<<n-index-1<<endl;
    for(int i=index+1; i<n;i++){
        cout<<id[i]<<endl;
    }
  //seperate the group B weak bacteria.
    cout<<index+1<<endl;
    for(int i=0; i<index+1;i++){
        cout<<id[i]<<endl;
    }

}




int main()
{
// input data to array.
int n=0;
cin>>n;

int id[100]={0};
double rate[100]={0};
for(int i=0; i<n; i++){
    int pre_num=0, pos_num=0;
    cin>>id[i]>>pre_num>>pos_num;
    // calculate the growth rate of each row.
    rate[i]= (double) pos_num/pre_num;
    
}


/*
// output the original array.
for(int i=0; i<n; i++){
    cout<< id[i]<<' '<<rate[i];
    cout<<endl;
}
*/


// calculate by function rate_sort()
rate_sort(n,id,rate);

    return 0;   
}

/*
example data
input 
5
1 10 3456
2 10 5644
3 10 4566
4 20 234
5 20 232


*/