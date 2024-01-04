#include<iostream>
#include<cmath>
using namespace std;

/* 
looking for prime within 100.
Sieve of Eratosthenes algorithm

how to remove the duplicate computing 10 times as below? 
3*2, 4*(2,3), 5*(2,3,4), 7*(2,3,4,5)
*/

int main()
{
    int sum=0, a[100]={0}, prime[4]={2,3,5,7};
    for(int i=2;i<=50;i++)
    {
        for(int j=0; j<4; j++)
        {
            sum= prime[j]*i;
            if(sum<100)
            a[sum]=1; // why = ?
        }


    }
    for(int i=2;i<100;i++)
    {
        if(a[i]==0)cout<<i<<" "; // why == ?
        
    }

    cout<<""<<endl;

	return 0;
}