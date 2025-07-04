/*
2. C程序设计进阶
5. 第五 module
2. 编程题＃2：二维数组右上左下遍历

给定一个row行col列的整数数组array，要求从array[0][0]元素开始，
按(从右上到左下)/(从左下到右上)的对角线顺序遍历整个数组。

eg. input 
3 5
1 2  4  7 10
3 5  8 11 13
6 9 12 14 15 
|0.0  0.1  0.2  0.3  0.4|
|1.0  1.1  1.2  1.3  1.4|
|2.0  2.1  2.2  2.3  2.4|

5 3
1   2   4
3   5   7
6   8  10 
9  11  13  
12 14  15 
|0.0  0.1  0.2|
|1.0  1.1  1.2|
|2.0  2.1  2.2|
|3.0  3.1  3.2|
|4.0  4.1  4.2|


output
1
2
3
4
5
6
7
8
9
10
11
12
*/
#include <iostream>
using namespace std;

//Traverse array from top right to bottom left. 
void Traverse(int **array, int row, int col){
    int i=0, j=0, k=0;
// firstly, traverse points starts from top row.
// i=0, j<col; 
    while(k<col){
        j=k;
        while(j>=0 && i<row){
            cout<<array[i][j]<<endl;
            i++;
            j--;               
        }
        i=0;
        k++;
    }
// then, traverse points starts from right colum. 
// i=1, i<row, j=col-1;   
    k=1;    
    while(k<row){
        i=k;
        j=col-1; 
        while(j>=0 && i<row){
            cout<<array[i][j]<<endl;
            i++;
            j--; 
        }
        k++;
    }
}

//Traverse array from left bottom to right top. 
// void Traverse(int **array, int row, int col){
//     for (int i = 0; i < row; ++i) {
//         for (int j = 0; j <= i && j < col; ++j) {
//             cout << array[i - j][j] << endl;
//         }
//     }

//     for (int j = 1; j < col; ++j) {
//         for (int i = 0; i < row && j + i < col; ++i) {
//             cout << array[row - i - 1][j + i] << endl;
//         }
//     }
// }

int main()
{
    // input arguments
    int row=0, col=0;
    cin>>row>>col;
    // create pointers
    int **array= new int*[row];
    for(int i=0; i<row; i++){
        array[i]= new int[col];
        for(int j=0; j<col; j++){
            cin>>array[i][j];
        }
    }
    Traverse(array, row, col);
    //deallocate memory
    for(int i=0; i<row; i++){
        delete [] array[i];
    }
    delete [] array;
    
    return 0;  
}