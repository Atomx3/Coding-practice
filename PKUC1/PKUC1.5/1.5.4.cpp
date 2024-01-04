#include <iostream>
using namespace std;



int main() {
    
   
    // input numbers;
    int p;
    cin >> p;
    
    // calculate the number of 1, loop;
    for(int i=0; i<p; i++){
    int n, r=0;
    cin >> n;
    while(n>0){
        r+=n%2;
        n/=2;
    }
    // output the nubmer of 1;
    cout<<r<<endl;

    }


    return 0;
}
//其实还有更快的算法你能想到吗？