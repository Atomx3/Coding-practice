#include <iostream>
#include <cstring>

using namespace std;

/*
编程题＃5：字符串插入
不使用strcat，strncpy

*/

int main()
{
// input two string, a gap between them
char str[10]={0}, substr[3]={0};
while(cin>>str>>substr){

// find the largest ascii value position.
int max_Ind=0;
for(int i=1; str[i]!='\0'; i++){
    if(str[i]>str[max_Ind]){
        max_Ind=i;
        }
}

// insert the short string to the long string.
char Nstr[13]={0};
for(int i=0; i<13;i++){
    if(i<max_Ind+1){Nstr[i]=str[i];}
    else if(i>max_Ind&&i<=max_Ind+3) {Nstr[i]=substr[i-max_Ind-1];}
    else {Nstr[i]=str[i-3];}
}

// output the New string
cout<<Nstr<<endl;

}


    return 0;   
}


/*
example data



*/