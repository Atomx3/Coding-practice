#include <iostream>
using namespace std;

int main() {

// input n, k, a[].
int n=0, k=0, a[n];
cin>>n;
cin>>k;
for(int i=0; i<n; i++){
    cin>>a[i];
};

// find the Biggest number.
int fstB =0;
for (int i= 0; i < n; i++)
{
if (a[i]>=fstB)
fstB=a[i];
}
cout<<fstB<<endl;


// find the Smallest number.
int fstS=a[0];
for (int i= 0; i < n; i++)
{
if (a[i]<=fstS)
fstS=a[i];
}
cout<<fstS<<endl;

int kthB=0;
// if k Big enough, count from Smallest number.
if(k> n/2 && k<=n){
    kthB=fstS;
    for (int i= 0; i < n; i++)
    {
        if (kthB - fstS<= a[i]- fstS)
        kthB=a[i];
    }
}
// if k Small enough, count from Biggest number.
else if (k<= n/2 ){
    kthB=fstB;
    for (int i= 0; i < n; i++)
    {
        if (a[i]<=kthB && kthB<fstB && kthB>=midB);
        else if(a[i]<=kthB && kthB<=midB);
        kthB=a[i];
    }
}

cout<<kthB<<endl;



    return 0;
    }
    

   