#include <iostream>
using namespace std;

/*
w10.
编程题＃2：忽略大小写，比较字符串ascii值大小
要求将大写字母的转换成小写字母，然后以字符串顺序比较大小；
https://www.coursera.org/learn/jisuanji-biancheng/programming/eWlOp/shu-zu-ying-yong-lian-xi
*/ 

int main()
{// input two line of strings.
    char s1[80] = {0}; // initialization assignment use = 
    char s2[80] = {0};
    cin.getline(s1, 80);
    cin.getline(s2, 80);

    
    // change the ASCII value of upper case to small case.
    int i = 0;
    while(i < 80 &&(s1[i] != 0 || s2[i] != 0))
    {   
// ’A‘ =65, 'Z'=90, both char and int are available to work.
        if (s1[i] >= 'A' && s1[i] <='Z') 
        //if (s1[i] >= 65 && s1[i] <=90) 
        {
            s1[i] += 32;
        }
         if (s2[i] >= 'A'&& s2[i] <='Z')
        //if (s2[i] >= 65&& s2[i] <=90)
        {
            s2[i] += 32;
        } 
        i++;
  
    }

    // compare the value of ASCII
        int j=0;
        char result= '0'; 
        while (s1[j]!='\0') 
        { 
            
        if (s1[j] == s2[j]) // conditional judgment statement == 
        {
            result='=';
            j++;
            continue;
        }
        else if (s1[j] > s2[j])
        {
            result='>';
            break;
        }
        else {
            result='<';
            break;
        }

        
        }
    
    
    cout<< result << endl;


    return 0;
}