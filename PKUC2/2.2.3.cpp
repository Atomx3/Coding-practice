#include <iostream>
#include <iomanip>
using namespace std;

/*
编程题＃3：发票统计

*/


int main()
{
    float fapiao[3][3]={0};
    for(int id=0;id<3;id++){
    int ID=0, N=0;
    cin>>ID>>N;
// input fapiao type and money.
        for(int type=0; type<N;type++){
            char TYPE=' '; float MONEY=0.0;
            cin>> TYPE>> MONEY;
// calculat the total amount of each type fapiao of each id.
            switch(TYPE){
                case'A':
                fapiao[ID-1][TYPE-'A']+=MONEY;
                break;
                case'B':
                fapiao[ID-1][TYPE-'A']+=MONEY;
                break;
                case'C':
                fapiao[ID-1][TYPE-'A']+=MONEY;
                break;
            }
            
        }
        
    }
// output the fapiao amount of each id.
// use id[id] instead of id+1 for ouput the id.
float sum_amount=0.0;
int ID[3]={1,2,3};
for(int id=0;id<3;id++){
    for(int type=0; type<3;type++){
    sum_amount+= fapiao[id][type];
    }
    cout<<ID[id]<<' '<<fixed<<setprecision(2)<<sum_amount<<endl;
    sum_amount=0.0;
}


// calculat the fapiao amount of each type, and output.
    char FType[3]={'A','B','C'};
        for(int type=0;type<3;type++){
            for(int id=0; id<3;id++){
                sum_amount+= fapiao[id][type];
                }
            cout<<FType[type]<<' '<<fixed<<setprecision(2)<<sum_amount<<endl;
            sum_amount=0.0;
            } 



    return 0;   
}

/*
example data
input 
1 5 A 1.0 A 2.0 C 1.0 B 1.0 C 1
3 3 B 1 C 2 C 1
2 4 B 1 A 1 C 1 A 1

output
1 6.00
2 4.00
3 4.00
A 5.00
B 3.00
C 6.00
*/