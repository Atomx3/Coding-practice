#include <iostream>
using namespace std;

int main() {
    // input 
    int n, x, y, left;
    cin >> n>> x>> y;
    left = n- y/x;

    // output.
    if(y%x!=0 && left>=1){    
        cout<< left -1 <<endl;
    }
    else if(left<0) {cout<< 0 <<endl;}
    else {cout<< left <<endl;}



    return 0;
}
