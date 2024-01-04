#include<iostream>
using namespace std;

int main(){
int n, m;
cin>> n;
cin>> m;

float timeWalk, timeBike;
timeWalk= (m*n)/1.2;
timeBike= n*(m/3 + 27+23);

if(timeWalk>timeBike){
    cout<<"Bike"<<endl;}
else if(timeWalk<timeBike){
    cout<<"Walk"<<endl;}
else {
    cout<<"Bike or Walk"<<endl;}
    
    return 0;
}
