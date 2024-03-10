/*
2. C程序设计进阶
9. 第9周
1. 编程题＃1：含k个3的数
*/
#include <iostream>
using namespace std;

void c3(int m, int k){
    int count3=0, nm=m;
    while(m !=0){
        int isit3 = m%10;
        if(isit3 ==3){
            count3++;
        }
        m /=10;
    }
    
    if(nm % 19 == 0 && k==count3){
        cout<<"YES"<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }
}

int main(){
    int m=0, k=0;
    // Keep asking for input until valid values are provided
    while(true){
        cin>>m>>k;
        // Check if input values are within valid range
        if (m > 1 && m < 100000 && k > 1 && k < 5) {
            break; // Exit the loop if valid input
        } 
        else {
            cout << "Invalid input. Please try again." << endl;
        }
    }
    //cout<<m<<" "<<k<<endl;
    c3(m,k);
    return 0;
}