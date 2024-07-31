#include<iostream>
using namespace std;


// the greatest common divisor function declaration
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    } else {
        return gcd(b, a % b);
    }
}


int main() {

// number n fractions;
  int n=0;
  cin>>n;

// input Fraction (x/y) and store in array f[n]
std::string f[n];
int x[n], y[n];
for(int i=0; i<n; i++){
        std::cin >> f[i];
// take out x, y value and change it to interger, store in array x[n],y[n];
// fraction such as 3/5, 6/17, 4/9...
        size_t pos = f[i].find("/");
        std::string x_str = f[i].substr(0, pos);
        std::string y_str = f[i].substr(pos + 1);
        x[i] = std::stoi(x_str);
        y[i] = std::stoi(y_str);

  }

// calculate the sum of Numerator and denominator（x,y) in fraction.
int sumx=x[0], sumy=y[0];
for(int i=1; i<n; i++){
sumx= sumx*y[i]+x[i]*sumy;
sumy*= y[i];
}

// test output x[], sum 
// cout<< x[1]<<"/"<<y[1]<<endl;
// cout<< sumx<<"/"<<sumy<<endl;


// find the gcd
int g= gcd(sumx,sumy);
if(sumx==sumy){
    std::cout<<"1/1"<<std::endl;}
else if (sumx!=sumy){
    std::cout<<sumx/g <<"/"<<sumy/g<<std::endl;
    }



  
  
  return 0;
}