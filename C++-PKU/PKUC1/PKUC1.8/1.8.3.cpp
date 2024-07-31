#include<iostream>
using namespace std;

int main(){
// input saving n which keep stable every year.
// input house price increasing rate k.
float n=0, k=0;
while(cin>>n>>k){

// set original house price 200.
float years=1, housePrice=200, saving=n;

    while(true){
    housePrice*=(1+k/100);
    saving+=n;

// count the years and calculate saving n and final house price.
// until find the mininum number of years, house is affordable to buy.
if(saving>=housePrice){
    cout<<years+1<<endl;
    break;}
  
// if the house is unaffordable within 20 years, print "impossible" to buy.
else if(years>19){
    cout<<"impossible"<<endl;
    break;} 

  years++;
    }

}

    return 0;
}

/* 
test, input values 
50 10
40 10
40 8

output values
8
Impossible
10
*/