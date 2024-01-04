#include <iostream>
#include <cstring>
using namespace std;

/*
w10.
sorting words from a sentence 
*/ 

int main()
{
// input sentence to array with the end of symbol '.'.
char str[500]={0};
cin.getline(str,500,'.');  


// sorting words from str[] to another array str_word[].
int j=0,i=0,word_index=0;
char word[500]="";
char str_word[500][500]={0};

while(i<strlen(str)){
    if (str[i]==' '){
        str_word[j][word_index]= '\0';
        word_index= 0;
        j++;
        }
    else{
        str_word[j][word_index]=str[i];
        word_index++;
        }
    i++;    
    }
str_word[j][word_index]='\0';

/*
//output the words array line by line from str_word.
int k=0;
while(k<=j&&str_word[k]!='\0'){
    cout<< str_word[k]<<endl;
    k++;   
}

// cout<< str_word[k][]<<endl; 
*/



// output the largest word's numbers.
int k=0, q=0, maxNum=0, maxIndex=0;
while (k<=j&& str_word[k]!='\0'){
    while(str_word[k][q]!='\0'){
        if(q>=maxNum){
        maxNum=q;
        maxIndex=k;
        q++;}

    }  

    k++; 
}


cout<< maxNum+1<<endl; 
// output the largest word.
cout<< str_word[maxIndex]<<endl; 

return 0;
    
}