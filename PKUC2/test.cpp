#include <iostream>
using namespace std;

/*

A,B,C,D four person, each one could only give one right char.
please find the four right chars, 
and output in the order of a[0][j]<<a[1][i]<<a[2][q]<<a[3][s] .
*/

int main()
{
// set 2D array and it's data.
/*
char
A[4]={'d',0,'p','h'},
B[4]={'h','p','t','d'},
C[4]={0,0,'d','h'},
D[4]={p,h,d,t};
*/
char a[4][4]={
{'d',' ','p','h'},
{'h','p','t','d'},
{' ',' ','d','h'},
{'p','h','d','t'}
};


for(int j=0; j<4; j++){
    for(int i=0; i<4; i++){ 
		for(int q=j+1; q<4; q++){
			for(int s=i+1; s<4; s++){
		
        if(
			(a[0][1]=='t')
        &&(a[2][0]=='t'||a[2][0]=='p') 
        && (a[2][1]=='t'||a[2][1]=='p')
		&& a[0][j]!=a[1][i]
		&& a[0][j]!=a[2][q]
		&& a[0][j]!=a[3][s]
		&& a[1][i]!=a[2][q]
		&& a[1][i]!=a[3][s]
		&& a[2][q]!=a[3][s]
		&& i+j+q+s+4 == 10
		&& (i+1)*(j+1)*(q+1)*(s+1)= 24)
            {
            cout<<a[0][j]<<a[1][i]<<a[2][q]<<a[3][s]<<endl;
            }
			}
			}

    }
    
}
cout<<endl;

/*

// test the output
for(int i=0; i<4; i++){
    int j=0;
    while(j<4){
        cout<<a[i][j]<<' ';
        j++;
    }
    cout<<endl;
}
cout<<endl;


*/

    return 0;   
}

/*
the correct output value will be
a[0][j] a[1][i] a[2][q] a[3][s]

p d t h 


*/