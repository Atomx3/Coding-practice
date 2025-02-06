#include <iostream>
using namespace std;

/*
编程题＃2：能被3，5，7整除的数

*/

int main()
{
// input a
int a=0;
while(cin>>a){
    if(a%3==0 && a%5==0 && a%7==0){
        cout<<"3"<<' '<<"5"<<' '<<"7"<<endl;
    }
    else if( a%3==0 && a%5==0){
        cout<<"3"<<' '<<"5"<<endl;
    }
    else if( a%3==0 && a%7==0 ){
        cout<<"3"<<' '<<"7"<<endl;
    }
    else if( a%5==0 && a%7==0 ){
        cout<<"5"<<' '<<"7"<<endl;
    }
    else if( a%3==0){
        cout<<"3"<<endl;
    }
    else if( a%5==0){
        cout<<"5"<<endl;
    }
    else if( a%7==0){
        cout<<"7"<<endl;
    }
    else if (a%3!=0 && a%5!=0 && a%7!=0){
        cout<<'n'<<endl;
    }

}
cout<<endl;


    return 0;   
}

/*
example data


*/