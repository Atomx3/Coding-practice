#include <iostream>
using namespace std;

/*
variable scope: global variables 
return variables change
*/


// case 1 exchange function.
int a=0, b=0;
void exchange(int& x, int& y)
{
    int p=0;
    if(x<y){
        p=x;x=y;y=p;
    }
}


// case 2 exchange function.
// 此处函数参数为空，因此也不能直接输入参数，不同于以上
int c=0, d=0;
void exchange()
{
    int p=0;
    if(c<d){
        p=c;c=d;d=p;
    }
}


/*
// case 3 change function.
此案例中未定义global variables, 
为何可以通过change函数改变另外一个main函数中的local variables的值呢？
*/
void change(int k[])
{
    k[0]=30; k[1]=50;
}



int main()
{
// case 1 exchange function.
cin>>a>>b;
exchange(a,b);
cout<<a<<' '<<b<<endl;

// case 2 exchange function.
/*
由于exchange 函数定义中，参数为空，不明确，
因此在输入时，也不能直接填入函数，与上面案例不同。*/

cin>>c>>d;
exchange();
cout<<c<<' '<<d<<endl;


/*
//case 3 change function.
array name k is not a variable, 
but a constant and the address of array in memory.
so it can change the variables in the memory, 
and this mechanism is different from the above 
case 1. global variables change.
k 作为数组名字，在此是常量（数组的内存地址），而非变量。
当main函数调用change函数时，
k作为参数输入给了change函数，
change函数访问了数组k[2]，
并在其中写入2个新的常量 k[0]=30; k[1]=50;
因此发生了神奇的事情：没有全局变量，局部变量，居然也被改变了。
缘由是，数组和内存地址访问，并被改写的结果。
}
*/

int k[2]={3,5};
change(k);
cout<<k[0]<<' '<<k[1]<<endl;




    return 0;   
}

/*
example data
input
3 5
3 5

output
5 3
30 50
*/