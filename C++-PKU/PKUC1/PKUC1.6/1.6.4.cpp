#include <iostream>
using namespace std;

int main() {

    // input n values, store in array t[n]
    int t[6];
    for(int i=0; i<6; i++){
        cin>>t[i]; 
    }

    // find the even number,store in even[j];
    int even[6], j=0;
    for(int i=0; i<6; i++){
        if(t[i]%2 == 0){
                even[j]= t[i];
                j++;
            }  
        }
    // find the min even=b in even[j];
    int b=even[0];
    for(int i=0; i<j; i++){
        if(even[i]<=b){
            b= even[i];
                }
            }

    // output;
    // cout<< b <<endl;

// find the odd number,store in odd[k];
    int odd[6], k=0;
    for(int i=0; i<6; i++){
        if(t[i]%2 == 1){
                odd[k]= t[i];
                k++;
            }  
        }
    // find the max odd=a in odd[k];
    int a=odd[0];
    for(int i=0; i<k; i++){
        if(odd[i]>=a){
            a= odd[i];
                }
            }

    // output;
    // cout<< a <<endl;

    // get the absolute value of a-b
    cout<<abs(a-b)<<endl;

    return 0;
    }
    

   