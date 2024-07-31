#include<iostream>
using namespace std;

int main(){
int n[6], i;
for(i=0; i<6; i++)
cin>> n[i];

int sum=0;
for(i=0; i<6; i++){
    if(n[i]<n[0]){sum+=n[i];}
}

cout<<sum<<endl;    
    
    return 0;
}
