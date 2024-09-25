#include <iostream>
using namespace std;

/*
3. C程序设计进阶
2. 第2周
1. 编程题＃1：寻找下标


*/

int main()
{
// input n
int n=1, x[99]={0};
cin>>n;
for(int i=0; i<n; i++){
cin>>x[i];
}


for(int i=0; i<n; i++){
    if(x[i]==i){
        cout<<i<<endl;
        i=n-1;
        
    } // what's the diffrence of 'N' and "N"? 
    else if(i==n-1 && x[i]!=i) {
        cout<<'N'<<endl;
    }
}



    return 0;   
}

/*
example data


*/