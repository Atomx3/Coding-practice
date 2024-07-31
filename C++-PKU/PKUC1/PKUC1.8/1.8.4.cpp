#include<iostream>
using namespace std;

int main()
{
// input n, k, and array a[n].
int n=0, k=0;
bool findK=false;
cin>>n>>k;

int a[n];
for(int i=0; i<n; i++){
    cin>>a[i];
}

// find out if there are two integers in the array a[] that the sum equal to k. 
for(int i=0; i<n; i++){
    for(int j=i+1; j<=n; j++){
        if(a[i]+a[j]==k){
        findK=true;
        break;
    }
    }    
}

if(findK==false)
    cout<<"no"<<endl;
else
    cout<<"yes"<<endl;

	return 0;
}