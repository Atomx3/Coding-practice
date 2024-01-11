#include <iostream>
using namespace std;

/*
variable scope: local variables
return no change 
*/


// case 1 exchange function.
int a=0, b=0;
void exchange(int a, int b)
{
    int p=0;
    if(a<b){
        p=a;a=b;b=p;
    }
}

/*
// case 2 change function.
此案例中未定义global variables, 
通过change函数，未能改变main函数中的local variables的值。
*/
void change(int k, int q)
{
    k=70; q=80;
}


int main()
{
// case 1 exchange function.
cin>>a>>b;
exchange(a,b);
cout<<a<<' '<<b<<endl;


/*
//case 2 change function.
此案例中，数组x的2个元素作为函数参数（常量）传递给函数change，
由于两个函数各自有局部变量，而且void没有返回值。

}
*/
int x[2]={7,8};
change(x[0],x[1]);
cout<<x[0]<<' '<<x[1]<<endl;

    return 0;   
}

/*
example data
input
3 5
3 5

output
3 5
3 5

*/