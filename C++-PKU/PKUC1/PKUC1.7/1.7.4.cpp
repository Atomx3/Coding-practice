#include <iostream>
using namespace std;



int main() {

// input m.
int m=0;
cin>>m;

// calculate max number of each kind of currency.
int n100=0, n50=0, n20=0, n10=0, n5=0, n1=0;
n100 = m/100; // 100 rmb, eg. 197
n50=(m%100)/50; // 50 rmb, max1, 97
// if(m%100>=50){n20=(m%100-50)%20;} // 20 rmb, max2, 50+47
n20=(m%100-50*n50)/20; // 20 rmb, max2, 47
n10=(m%100-50*n50-20*n20)/10; // 10 rmb, 17
n5= (m%100-50*n50-20*n20-10*n10)/5; // 5 rmb, 8, 3
n1= (m%100-50*n50-20*n20-10*n10-5*n5)/1; // 5 rmb, 3

// output
    cout<< n100 <<endl; 
    cout<< n50 <<endl; 
    cout<< n20 <<endl; 
    cout<< n10 <<endl; 
    cout<< n5 <<endl; 
    cout<< n1 <<endl;

    return 0;
    }
    

   