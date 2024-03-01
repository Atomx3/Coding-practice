/*
2. C程序设计进阶
3. 第三周
3. 编程题＃4：扩号匹配问题
find pair of parenthesis in the array by recursion.
the nearest boy(left side of parenthesis ) and girl(ride side of parenthesis), ignor the space.
until all pairs of parenthesis are matched, then output the new array;
maybe not all parenthesis(boy, girl) are matched. similar to previous 2.3.3 subject.
*/
#include <iostream>
using namespace std;

// remove the alphabet, leave with space in the array.
void remove(char *str)
{
    int i=0;
    while(str[i]!='\0'){
        if ((str[i] >= 'A' && str[i] <= 'Z')
        ||(str[i] >= 'a' && str[i] <= 'z')){
            str[i] = ' ';
        }
        //cout<<str[i];
        i++;
    }
    // number of the char in array;
    //cout<<i<<endl;
}

// Recursively find the next pair
void find_pair(char *str){
    int i = 0;
    remove(str);
    char  boy= '(', girl= ')';
    while(str[i] != '\0'){
        if(str[i] == boy){
            int j = i + 1;
            while(str[j] != '\0') { 
                if(str[j] == girl){
                str[i]=' ';
                str[j]=' ';
                find_pair(str); 
                return ;
                }
                // If we find another boy before a girl, break, i++     
                if(str[j] == boy) break; 
                j++;
            } 
        }
        i++;
    }
}

void rewrite(char *str){

    int i=0;
    // str = find_pair(str); 
    // above assignment expression doesn't work, 
    // because function return type is void, can not return value.
    // just call the function as below.
    find_pair(str);
    while(str[i]!='\0')
    {
        if(str[i]== '(')
            str[i]= '$';
        if(str[i]== ')')
            str[i]= '?';
        i++;
    }
    cout<<str<<endl;
}

int main()
{
    char boygirls[101];
    // cin >> boygirls; // not appropriate, only read and input char before space.
    while(cin.getline(boygirls,101)){
        //remove(boygirls);
        //find_pair(boygirls);
        cout << boygirls<<endl;
        rewrite(boygirls);
    }
    return 0;
}


/*
example data
input: ((ABCD(x)
output:((
boygirls[0], [13], [14]

input:)(rttyy())sss)(
output:)           )(
boygirls[0], [1]

input: (AB(cd(ll)f(gk)))(op)l(cdl()l))(llq)) 
output:                              )     )

*/