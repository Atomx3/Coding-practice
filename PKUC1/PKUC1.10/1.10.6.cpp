#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

/*
w10.
编程题＃6：循环移动
*/ 

int main()
{

// input n,m and array a[n]
int n=0, m=0, i=1;
cin>>n>>m;
// vector automatically handles dynamic memory allocation 
vector<int> a(n,1);

while(i<n+1){
    cin>>a[i];
    i++;
}
cout<<endl;



// allocate the elements of array
for(int k=1; k<m+1; k++){
    int q=n, temp=a[n];
    while(q>1){
        a[q]=a[q-1];
        q--;
    }
    a[1]=temp;
}



// output the new array a[n]
for(int j=1; j<n+1; j++){
    cout<<a[j]<<" ";
}
cout<<endl;

return 0;   
}

/*
example data

11 4
15 3 76 67 84 87 13 67 45 34 45
*/