#include <iostream>
using namespace std;

int main() {
    // input n values;
    int n;
    cin>>n;

    // seperate decimal;
    int x, y, z;
    x= n/100;
    y= (n%100)/10;
    z= (n%100)%10;

    // output;
    cout<< x <<endl;
    cout<< y <<endl;
    cout<< z <<endl;
    

    return 0;
}
