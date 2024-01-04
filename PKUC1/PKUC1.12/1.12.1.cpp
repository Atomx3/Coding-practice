#include <iostream>
using namespace std;

/*
编程题＃1：判断闰年

*/

int main()
{
// input a
int a=1;
while(cin>>a && a>0 && a<3000){
    if((a%4==0 && a%100!=0)||(a%400==0)){
    cout<< "Y"<<endl; 
    }
    else{
    cout<< "N"<<endl; 
    }
}
cout<<endl;


    return 0;   
}

/*
example data


*/