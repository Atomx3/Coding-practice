#include <iostream>
#include <iomanip>
using namespace std;

/*
w10.
编程题＃5：异常细胞检测
*/ 

int main()
{

// input integers N and array matrix of NxN.
int N=0, i=0, j=0, a[100][100]={0};
cin>>N;

while(i<N){
    j=0;
    while(j<N){
        cin>>a[i][j];
        j++;
    }
    i++;
}

// calculate the irregular cell number.
int Ir_num=0;
for(int k=0; k<N-2; k++){
    for(int q=0; q<N-2; q++){
        if( a[k][q+1]-a[k+1][q+1]>=50&&
            a[k+1][q]-a[k+1][q+1]>=50&&
            a[k+1][q+2]-a[k+1][q+1]>=50&&
            a[k+2][q+1]-a[k+1][q+1]>=50)
       Ir_num++;
    }
}

cout<<Ir_num<<endl;


/*
// output cell[N][N]array
int k=0, q=0;
while(k<N){
    q=0;
    while(q<N){
        cout<<setw(4)<<cell[k][q];
        q++;
    }
    k++;
    cout<< endl;
    
}
*/

return 0;   
}

/*
example data
5

70 70 70 70 80
70 10 70 10 60
70 70 20 80 20  
70 70 70 20 80
70 70 70 70 80

*/