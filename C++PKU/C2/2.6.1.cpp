/*
2. C程序设计进阶
6. 第六 module
1. 编程题＃1：分配病房
c++,
input patient's number(int) on array[j][2] colum[0], health metric(float, 1 decimal ) on colum[1]
check out the patients whose health metric reach sick threshold a (float 2 decimals), and 
store those patients' data in a new array n_arr[i][2]

why do it output the n, and n_index as the same value of m? 
it's impossible that only a part of patients have reached sick threshold a. 

why it is failed by the official evaluation? but the final result output is the same as official platform's. 
*/

#include <iostream>
#include <iomanip>
using namespace std;

void bubsort(int **n_arr, int n){
    for(int i=0; i<n; ++i){
        for(int j=0; j<n-i-1; ++j){
            if(n_arr[j][1] < n_arr[j+1][1]){
                swap(n_arr[j],n_arr[j+1]);
            }
        }
    }
    // output the new array of serious patients
    for(int i=0; i<n; i++){
        cout<<setw(3)<<setfill('0')<<n_arr[i][0]<<" ";
        cout<<fixed<<setprecision(1)<<*reinterpret_cast<float*>(&n_arr[i][1])<<endl;
    }

}

void Patients(int **array, int m, float a){
    int n=0;
    for(int j=0; j<m; j++){
        if(*reinterpret_cast<float*>(&array[j][1]) >= a){
            n++;
        }
    }
    // cout<<n<<endl;// the serious patien's number
    if(n==0){
        cout<<"None"<<endl;
        return;
    }

    // new array stores the serious patient's data.
    int **n_arr = new int*[n];
    for(int i=0; i<n; i++){
        n_arr[i]= new int[2];
    }
    
    // copy the serious patients' data to a new array
    int n_index=0;
    for(int j=0; j<m; j++){
        if(*reinterpret_cast<float*>(&array[j][1]) >= a){
            n_arr[n_index][0]=array[j][0];
            n_arr[n_index][1]=array[j][1];
            n_index++;
        }
    }
    // sorting the array in decrement order of health situation. 
    bubsort(n_arr, n);
    // Deallocate memory
    for (int i = 0; i < n; ++i) {
        delete[] n_arr[i];
    }
    delete[] n_arr;

}

int main(){
    int m=0; 
    float a=0.00;
    cin>>m;
    cin>>a;

    // Allocate memory for the 2D array
    int **array = new int*[50];
    for(int i=0; i<m; i++){
        array[i]= new int[2];
    }
    // input two type of data on columns (0: int, 1: float)
    for(int i=0; i<m; i++){
        cin>>array[i][0];
        //cin>>array[i][1];
        cin>>*reinterpret_cast<float*>(&array[i][1]);
    }
    // output the original array.
    // for(int i=0; i<m; i++){
    //     cout<<setw(3)<<setfill('0')<<array[i][0]<<" ";
    //     //cout<<array[i][1]<<endl;
    //     cout<<fixed<<setprecision(1)<<*reinterpret_cast<float*>(&array[i][1])<<endl;
    // }
    Patients(array, m, a);
    // Deallocate memory
    for (int i = 0; i < m; ++i) {
        delete[] array[i];
    }
    delete[] array;
    return 0;
}
