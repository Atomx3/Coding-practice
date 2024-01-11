#include <iostream>
using namespace std;

/*
编程题＃2：四大湖
there are four lakes p, d, t, h, the area size are different from each other;
four persons, each one could only tell one right rank number of the lake size.
please find the four right ranke number. 

// set 2D array and data.
char
A[4]={'d',0,'p','h'},
B[4]={'h','p','t','d'},
C[4]={0,0,'d','h'},
D[4]={p,h,d,t};

char a[4][4]={
{'d',' ','p','h'},
{'h','p','t','d'},
{' ',' ','d','h'},
{'p','h','d','t'}
};

*/

int main()
{   // set four lakes name, initial value 1 and possible rank;
    int p, d, t, h;
    for(p=1;p<=4;p++){
        for(d=1;d<=4;d++){
            for(t=1;t<=4;t++){
                for(h=1;h<=4;h++){
// each lakes has different size rank.
                    if( (p!=d&& p!=t&& p!=h&& d!=t&& d!=h&& t!=h)
// each person has only one true answer.
//  which return value 1, other wise return 0. 
                    && ((d==1)+(h==4)+(p==3)==1)
                    && ((h==1)+(d==4)+(p==2)+(t==3)==1)
                    && ((h==4)+(d==3)==1)
                    && ((p==1)+(t==4)+(h==2)+(d==3)==1)
                    )
                    {
                        cout<<p<<' '<<d<<' '<<t<<' '<<h<<endl;
                    }

                }
            }
        }
    }





/*
char Na[4]={0};
for(int j=0; j<4; j++){
    for(int i=0; i<4; i++){ 
        if(Na[j]=='d'||Na[j]=='p'||Na[j]=='h'||Na[j]=='t'
        && (a[0][1]=='t') 
        &&(a[2][0]=='t'||a[2][0]=='p') 
        && (a[2][1]=='t'||a[2][1]=='p'))
            {
            Na[j]=a[i][j];
            }

    }
    
}
cout<<endl;

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
example data


*/