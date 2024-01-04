#include <iostream>
using namespace std;

int main() {

// input n
int n=0;
cin>>n;

if(95<=n && n<=100)
cout<< 1 <<endl;
else if(90<=n && n<95)
cout<< "2" <<endl;
else if(85<=n && n<90)
cout<< 3 <<endl;
else if(80<=n && n<85)
cout<< 4 <<endl;
else if(70<=n && n<80)
cout<< 5 <<endl;
else if(60<=n && n<70)
cout<< 6 <<endl;
else if (n>=0 & n<60)
cout<< 7 <<endl;
else
cout<< "please input right number shold be  0 <= n <= 100" <<endl;

    return 0;
    }
    

   