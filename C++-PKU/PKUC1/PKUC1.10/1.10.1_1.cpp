#include <iostream>
#include <string>
using namespace std;
int main(){
/*
编程题＃1：求字母的个数
*/

int counts=0;
string s[80];
for(counts=0; s[counts]!='\0'; counts++){
    cin.getline(s,counts);
}

// count letters a, e, i, o, u in the string array s.
int i=0, countsA=0, countsE=0, countsI=0, countsO=0, countsU=0 ; 
    while(s[i]!='\0'){
        if (s[i]=='a') {countsA++;}
        else if (s[i]=='e'){countsE++;}
        else if (s[i]=='i') {countsI++;}
        else if (s[i]=='o') {countsO++;}
        else if (s[i]=='u') {countsU++;}
        i++;
    }
s[i]='\0';

cout<<countsA<<countsE<<countsI<<countsO<<countsU<<endl;
    

	return 0;
}