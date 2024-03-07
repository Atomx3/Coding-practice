/*
2. C程序设计进阶
6. 第六周
2. 编程题＃2：配对碱基链
c++,
描述
脱氧核糖核酸（DNA）由两条互补的碱基链以双螺旋的方式结合而成。而构成DNA的碱基共有4种，分别为腺瞟呤（A）、鸟嘌呤（G）、胸腺嘧啶（T）和胞嘧啶（C）。我们知道，在两条互补碱基链的对应位置上，腺瞟呤总是和胸腺嘧啶配对，鸟嘌呤总是和胞嘧啶配对。你的任务就是根据一条单链上的碱基序列，给出对应的互补链上的碱基序列。

输入
第一行是一个正整数n，表明共有n条要求解的碱基链。

以下共有n行，每行用一个字符串表示一条碱基链。这个字符串只含有大写字母A、T、G、C，分别表示腺瞟呤、胸腺嘧啶、鸟嘌呤和胞嘧啶。每条碱基链的长度都不超过255。

输出
共有n行，每行为一个只含有大写字母A、T、G、C的字符串。分别为与输入的各碱基链互补的碱基链。
*/


#include <iostream>
using namespace std;

void atgc(char **dna, int n){
    for(int i=0; i<n; i++){
        int j=0;
        while(dna[i][j]!='\0'){
            if(dna[i][j] == 'A'){
                dna[i][j]= 'T';
            }
            else if(dna[i][j] == 'T'){
                dna[i][j]= 'A';
            }
            else if(dna[i][j] == 'G'){
                dna[i][j]= 'C';
            }
            else if(dna[i][j] == 'C'){
                dna[i][j]= 'G';
            }           
            j++;
        }
    }
    //output the original array
    for(int i=0; i<n; i++){
        cout<<dna[i]<<endl;
    }
}

int main(){
    int n=0;
    cin>>n;

    char **dna = new char*[n];
    for(int i=0; i<n; i++){
        dna[i]= new char[255];
        cin>>dna[i];
    }
    atgc(dna, n);
    //output the original array
    // for(int i=0; i<n; i++){
    //     cout<<dna[i]<<endl;
    // }
    for(int i=0; i<n; i++){
        delete[] dna[i];
    }
    delete[] dna;

    return 0;
}