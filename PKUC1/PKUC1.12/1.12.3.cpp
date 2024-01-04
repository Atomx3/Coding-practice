#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

/*
编程题＃3：最远距离

*/

int main()
{
// input n
int n=0;
cin>>n;
// input 2D matrix array a, dynamic memory allocation.

vector< vector<double> > a(n,vector<double>(2));
for(int i=0;i<n;i++){
    int j=0; 
    while(j<2){
        cin>>a[i][j];
        j++;
    }
    
}
cout<<endl;


// calculate the largest distance between two coordinate point.
double dist=0, maxDist=0;
int i=0;
while(i<n){
    for(int j=i+1; j<n; j++){
        dist= sqrt(pow(a[i][0]-a[j][0],2)+pow(a[i][1]-a[j][1],2));
        if(maxDist<dist){
            maxDist=dist;
            }
    }
    i++;
}

cout<<fixed<<setprecision(4)<<maxDist<<endl;



/*

// output the array a[n][2]
int i=0;
while(i<n){
    for(int j=0; j<2; j++){
        cout<<fixed<<setprecision(1)<<a[i][j]<<' ';
    }
    i++;
    cout<<endl;
}

// find the largest and smallest number;
int k=0;
double largN=a[0][0], smalN=a[0][0];
while(k<n){
    for(int j=0; j<2; j++){
        if(a[k][j]>=largN){
            largN=a[k][j];
        }
        else if(a[k][j]<=smalN)
        {
            smalN=a[k][j];
        }
    }
    k++;
}
*/



    return 0;   
}


/*
example data

intput
6
34.0 23.0
28.1 21.6
14.7 17.1
17.0 27.2
34.7 67.1
29.3 65.1


output 
53.8516

*/