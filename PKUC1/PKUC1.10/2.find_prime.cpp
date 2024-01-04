#include<iostream>
#include<cmath>
using namespace std;

/* 
looking for prime within 100.
https://www.coursera.org/learn/jisuanji-biancheng/lecture/a53He/shu-zu-de-zuo-yong-zhi-er
Sieve of Eratosthenes algorithm
*/

int main()
{
    int sum=0, a[100]={0};
    for(int i=2;i<sqrt(100.0);i++)
    {
        sum=i;
        while(sum<100)
        {
            sum=sum+i;
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