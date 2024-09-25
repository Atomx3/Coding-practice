#include <iostream>
#include <iomanip>
using namespace std;

/*
w10.
编程题＃4：矩阵交换行

*/ 

int main()
{

// input matrix of integers 5X5 

/* if initialize as char a[], have to use cin.getline which 
is typically used for reading as strings, not integers.
and then parse the string to extract the integers, and 
need sscanf() or strtol() to parse the integers.
 */
int i=0, j=0, n=0, m=0;
int a[5][5]={0}; 
while(i<5){
    j=0;
    while(j<5){
        cin>>a[i][j];
        j++;
    }
    i++;
}
cin>>n>>m;


// compare n,m with i, j
if((0>n||n>=i) || (0>m||m>=j)){
    cout<<"error"<<endl;
}
else{
// exchange the n,m line string in the array a[]
    int tem_a[5]={0};
    for(int p=0; p<5;p++){ 
        tem_a[p]=a[n][p];
        a[n][p]=a[m][p];
        a[m][p]=tem_a[p];
    }

// output the array a[k]
    int k=0, q=0;
    while(k<5){
        q=0;
        while(q<5){
            cout<< setw(4)<< a[k][q];
            q++;
        }
        k++;
        cout << endl;  
    }
}




return 0;
    
}

/*
example data
1 2 2 1 2
5 6 7 8 3
9 3 0 5 3
7 2 1 4 6
3 0 8 2 4

0 4
*/