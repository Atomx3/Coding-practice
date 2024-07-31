#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

/*
w10.
编程题＃7：中位数
*/ 

int main()
{

// input N, array a[] request integer line by line.
int n=0;
cin>>n;

// vector automatically handles dynamic memory allocation 
vector<int> a(n,1);
int i=n;
while(i>0){
    cin>>a[i];
    i--;
}


int midNum=0;
if (n%2==0){
    midNum=(a[n/2]+a[n/2+1])/2;
}
else midNum=a[n/2+1];


// output 
cout<<midNum<<endl;

return 0;   
}

/*
example data
11
15 3 76 67 84 87 13 67 45 34 45
*/