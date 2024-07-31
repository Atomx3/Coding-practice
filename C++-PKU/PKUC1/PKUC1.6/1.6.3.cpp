#include <iostream>
using namespace std;

int main() {
    // input n>=1, <=100. 
    int n, t[n];
    cin>>n;

    // input array with each value [0, 100], and store in t[n], 
    for(int i=0; i<n; i++){
        cin>>t[i]; 
    }
 
    // find the max value Hn in t[i];
    int Hn=0;
    for(int i=0; i<n; i++){
        if(t[i]>=0 && t[i]<=100 && t[i]>=Hn){
            Hn= t[i];
        }
    }

    // output;
    cout<<Hn<<endl;
    


    return 0;
}
