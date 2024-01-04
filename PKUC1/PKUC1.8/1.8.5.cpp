#include <iostream>
using namespace std;
int main(){
/*
对一个整数n,如果其各个位数的数字相加得到的数m能整除n,
则称n为自整除数.例如21,21%(2+1)==0,所以21是自整除数.
现求出从10到n(n < 100)之间的所有自整除数.
*/

int n=0, m=0;
cin>>n;

// find all i
for(int i=10; i<=n; i++){
    m=i/10+i%10;
    if(i%m==0){
        cout<<i<<endl;
    }
    
    
}
    

	return 0;
}