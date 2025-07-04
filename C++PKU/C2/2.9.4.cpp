/*
2. C程序设计进阶
9. 第9 module
4. 编程题＃4：寻找平面上的极大点
*/
#include <iostream>
using namespace std;

void max_c(int **cor, int n){
    int maxx=0; // find the max int on x coordinate.
    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(cor[i][0] == cor[j][0]){
                if(cor[j][1] > cor[i][1]){
                cor[i][1]=cor[j][1];
                cor[j][1]= -1;
                cor[j][0]= -1;
                }
                else{
                cor[j][1]= -1;
                cor[j][0]= -1;
                }
            }
        }
        if(cor[i][0]>maxx){
            maxx=cor[i][0];
        }
    }
    // output the new array with max coordinate 
    // for(int i=0; i<n; i++){
    //     cout<<cor[i][0]<<" "<<cor[i][1]<<endl;
    // }

    for(int x=0; x<101; x++){
        for(int i=0; i<n; i++){
            if(cor[i][0]==x){
                cout<<"("<<cor[i][0]<<","<<cor[i][1]<<")";
                if(x!=maxx){
                    cout<<",";
                }
            }
        }
    }
}

int main(){
    int n=0;
    while(true){
        cin>>n;
        // Check if input values are within valid range
        if(n>0 && n<=100){
            break;// Exit the loop if valid input
        } 
        else{
            cout << "Invalid input. try again." << endl;
        }

    }
    
    int **coordinate = new int*[n];
    for(int i=0; i<n; i++){
        coordinate[i]= new int[2];
        for(int j=0; j<2; j++){
            cin>>coordinate[i][j];
            // Check if coordinates are within valid range
            if (coordinate[i][j] < 0 || coordinate[i][j] > 100) {
                cout << "Invalid, must be between 0 and 100." << endl;
                j--; // Retry input for the same coordinate
            }
        }
    }

    // for(int i=0; i<n; i++){
    //     for(int j=0; j<2; j++){
    //         cout<<coordinate[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    max_c(coordinate, n);

    for(int i=0; i<n; i++){
        delete[] coordinate[i];
    }
    delete[] coordinate;
    return 0;
    
}