/*
2. C程序设计进阶
5. 第三周
1. 编程题＃1：计算矩阵边缘元素之和

eg. input and output
2
4 4
1 1 1 1
0 0 0 0
1 0 1 0
0 0 0 0
3 3
3 4 1
3 7 1
2 0 1

5
15
*/
#include <iostream>
using namespace std;

int edgeSum(int m, int n, int **matrix){
    int sum=0;
    for (int j=0; j<n; j++){
        // sum the first and last row
        sum+= matrix[0][j] + matrix[m-1][j];
    }
    for(int i=1; i<m-1; i++){
        // sum the first colum and last colum
        sum += matrix[i][0] + matrix[i][n-1];
    }
    cout<<sum<<endl;

    //deallocate memory
    for(int i=0; i<m; i++){
        delete [] matrix[i];
    }
    delete [] matrix;
    return 0;
}

int main()
{
    // input arguments
    int k=0, m=0, n=0;
    cin>>k;
    int **matrix; // declare secondary pointer matrix[m][n]
    for(int x=0; x<k; x++){
        cin>>m>>n;
        // Check if m and n are less than 100
        if(m >= 100 || n >= 100){
            cout << "Error: m and n must be less than 100" << endl;
            continue;
        }
        matrix= new int*[m];//create m rows of array to pointer matrix
        for(int i=0; i<m; i++){
            matrix[i]= new int[n];// create m colums of array to poiter matrix[]
            for(int j=0; j<n; j++){
                cin>>matrix[i][j];
            }
        }
        //call function and calculate.
        edgeSum(m,n,matrix);
    }
    
    
    //output the matrix
    // for(int i=0; i<m; i++){
    //     for(int j=0; j<n; j++){
    //         cout<<matrix[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    return 0;  
}
