#include <iostream>
using namespace std;

int main() {
    
    // users input two number
    int m, n;
    cin>> m >> n;
    // if wrong numbers, warning users to input it again;
    //if(m>n|| m<0|| n>300){
    //    cout<<"Wrong, please input number such as 0<=m<=n<=300"<<endl;} 
    
    // looking for Odd number, and store it in array;
    int x=0;
    int numOdd[300];
    for(int i=m; i<n+1; i++){
        
    if (i%2==1){
        numOdd[x]=i;
        x++;
    }

    }


    // sum the array elements and output;
    int sum=0;
    for(int i=0; i<x+1; i++)
    {sum+= numOdd[i];}
    cout<<sum<<endl;


return 0;
}
