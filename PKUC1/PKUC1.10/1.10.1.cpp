#include <iostream>
#include <string>
using namespace std;
int main(){
/*
编程题＃1：求字母的个数
*/


char s[80]={0};
cin.getline(s,80);


// count letters a, e, i, o, u in the string array s.
int i=0, countsA=0, countsE=0, countsI=0, countsO=0, countsU=0 ; 
    while(s[i]!='\0'){
        if (s[i]=='a'||s[i]=='A') {countsA++;}
        else if (s[i]=='e'){countsE++;}
        else if (s[i]=='i'|| s[i]=='I') {countsI++;}
        else if (s[i]=='o') {countsO++;}
        else if (s[i]=='u') {countsU++;}
        i++;
    }

cout<<countsA<<" "<<countsE<<" "<<countsI<<" "<<countsO<<" "<<countsU<<endl;
// cout<<i<<endl; the number of chars;   

	return 0;
}