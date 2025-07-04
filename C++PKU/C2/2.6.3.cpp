/*
2. C程序设计进阶
6. 第六 module
3. 编程题＃3：寻找山顶
Subject description: find the max int.
input 2D array (m * n) with integers, 
compare int array[i][j] with it's neighbours on four dimension.
up: array[i-1][j];
down: array[i+1][j];
left: array[i][j-1];
right: array[i][j+1];
when array[i][j] on the edge bound, how to ignore the neighbours that does not exist, 
such as mot[-1][j], mot[m+1][j], mot[i][-1], mot[i][n+1]).

the max int array[i][j] must be larger than all it's neighbours.
then output the index(i, j) of max int.

requirement: c++, pointers
which header does this program need?
*/

#include <iostream>
using namespace std;

void top(int **mot, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
//how to ignore the index that does not exist, such as mot[-1][j], mot[m+1][j], mot[i][-1], mot[i][n+1])
            if(i==0){
                if(j==0){
                    if(mot[i][j]>=mot[i+1][j] && mot[i][j]>=mot[i][j+1]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
                else if(j>0 && j< n-1){
                    if(mot[i][j]>=mot[i][j-1] && mot[i][j]>=mot[i][j+1]
                        && mot[i][j]>=mot[i+1][j]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
                else if(j==n-1){
                    if(mot[i][j]>=mot[i][j-1] && mot[i][j]>=mot[i+1][j]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
            }
            
            if(i>0 && i<m-1){
                if(j==0){
                    if(mot[i][j]>=mot[i-1][j] && mot[i][j]>=mot[i+1][j]
                        && mot[i][j]>=mot[i][j+1]){
                            cout<< i <<" "<< j<< endl;
                    }
                }
                else if(j>0 && j< n-1){
                    if(mot[i][j]>=mot[i-1][j] && mot[i][j]>=mot[i+1][j]
                        && mot[i][j]>=mot[i][j-1] && mot[i][j]>=mot[i][j+1]){
                            cout<< i <<" "<< j<< endl;
                        }
                }
                else if(j==n-1){
                    if(mot[i][j]>=mot[i-1][j] && mot[i][j]>=mot[i+1][j]
                        && mot[i][j]>=mot[i][j-1]){
                            cout<< i <<" "<< j<< endl;
                    }
                }
            }
            if(i==m-1){
                if(j==0){
                    if(mot[i][j]>=mot[i-1][j] && mot[i][j]>=mot[i][j+1]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
                else if(j>0 && j< n-1){
                    if(mot[i][j]>=mot[i][j-1] && mot[i][j]>=mot[i][j+1]
                        && mot[i][j]>=mot[i-1][j]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
                else if(j==n-1){
                    if(mot[i][j]>=mot[i-1][j] && mot[i][j]>=mot[i][j-1]){
                        cout<< i <<" "<< j<< endl;
                    }
                }
            }
        }
    }
}

int main(){
    int m=0, n=0;
    cin>> m>> n;
    int **mountain = new int*[m];
    for(int i=0; i<m; i++){
        mountain[i]= new int[n];
        for(int j=0; j<n; j++){
            cin>>mountain[i][j];
        }
    }
    // output original array;
    // for(int i=0; i<m; i++){
    //     for(int j=0; j<n; j++){
    //         cout<<mountain[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    top(mountain, m, n);
    for(int i=0; i<m; i++){
        delete[] mountain[i];
    }
    delete[] mountain; 
    return 0;
}
