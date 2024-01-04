#include <iostream>
using namespace std;
int main() {
    
    // input ;
    int n, a[100];
    cin>> n;
    
    // reverse the array;
    for(int i=0; i<n; i++)
        cin>> a[i];
    while(n--){
        cout<<a[n];
        if(n>0)
        cout<<" ";
        }  

    return 0;
}
