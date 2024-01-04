#include <iostream>
using namespace std;

int main() {
    // input 
    int h, r, n;
    double pi=3.142596, volume;
    cin >> h>> r;
    volume= pi*r*r*h;

    // get an integer n value;
    n= int((20*1000)/volume);

    // output,  n must be a float, add 1;
     
       cout<< n+1 << endl;
   


    return 0;
}
