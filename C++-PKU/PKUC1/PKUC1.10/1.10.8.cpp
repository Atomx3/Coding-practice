#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
w10.
编程题＃8：校门外的树
*/ 

int main()
{

// input L, M
int L=0, M=0;
cin>>L>>M;

// input M*2 matrix array a[M][2]
// vector automatically handles dynamic memory allocation 
vector< vector<int> > a(M,vector<int>(2));
    for(int i=0; i<M; i++){
        for(int j=0; j<2; j++){
            cin>>a[i][j];
        }
    }

/*
// the decrement order input will cause wrong output numbers, why?
vector< vector<int> > a(M,vector<int>(2));
for(int i=M-1; i>-1; i--){
    int j=1;
    while(j>-1){
    cin>>a[i][j];
    j--;
    }
cout<<endl;
}
*/



    // calculate the tree cut numbers.
    int xTree=0;
    for(int i=0; i<M; i++){
        xTree+=a[i][1]-a[i][0]+1;
    }

    // calculate the intersection numbers.
    int intSec=0;
    for(int i=0; i<M-1; i++){
        int j=i+1;
        while(j<M){
            if(a[j][1]>=a[i][0]&&a[j][1]<=a[i][1]){
                intSec+=std::min(a[j][1],a[i][1])-std::max(a[i][0],a[j][0])+1;
            }
        j++;
        }
        
        
    }
        
    cout<<L+1-xTree+intSec<<endl;

/*

// output the array a[][] in order of decrement;
for(int i=M-1;i>-1;i--){
    int j=1;
    while(j>-1){
        cout<<a[i][j]<<' ';
        j--;
        }
    cout<<endl;
}
*/

return 0;   
}



/*
example data
500 3
150 300
100 200
470 471

500 3
100 200
150 160
180 190

*/
