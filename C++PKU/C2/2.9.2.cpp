/*
2. C程序设计进阶
9. 第9 module
2. 编程题＃2：字符串中次数第2多的字母
*/
#include <iostream>
using namespace std;

void max2nd(char *chr_c, int *chr_i, int num){
   
    int max=0;
    for(int i=0; i<num; i++){
        if(chr_i[i]>max){
            max= chr_i[i];
        } 
    }
    //cout<<max<<endl;

    int max2= max-1;
    while(max2>=0){
        int i=0;
        while(i<num){
            if(chr_i[i]==max2){
                if(chr_c[i]>='a'&& chr_c[i]<='z'){
                    cout<< static_cast<char>(chr_c[i]-32)<<"+"<<chr_c[i]<<":"<<max2<<endl;
                    //because operator of -subtraction or +add, 
                    // it transfer char to int type, ascii table doesn't work here.
                    //cout<< chr_c[i]-32 <<"+"<<chr_c[i]<<":"<<max2<<endl;
                    return;
                }
                else if(chr_c[i]>='A'&& chr_c[i]<='Z'){
                    cout<<chr_c[i]<<"+"<< static_cast<char>(chr_c[i]+32)<<":"<<max2<<endl;
                    return;
                }
            
            }
            else{
                i++;
            } 
        }
        max2--;
    }

}

void countalphabet(char *chr, int num){
    // create pointer for chars are counted.
    char *chr_c = new char[num];
    int *chr_i = new int[num];

    int i=0;
    while(i<num-1){
        if(chr[i]>='a' && chr[i]<='z' || chr[i]>='A' && chr[i]<='Z'){
            chr_c[i]=chr[i]; 
            int count=1;

            int j=i+1;
            while(chr[j]!='\0'){
                if(chr[j]==chr[i] || chr[j]==chr[i]+32 || chr[j]==chr[i]-32){
                count++;    
                chr[j]=33;
                }
                else{
                    if(chr[num-1]==33){
                        chr_i[num-1]=0;
                    }
                    else{
                        chr_i[num-1]=1;
                    }
                    chr_c[num-1]=chr[num-1];
                }
                j++;
            }
            chr_i[i]=count;
            chr[i]=33;
            
        }
        else{
            chr[i]= 33;
            chr_c[i]=33;
            chr_i[i]=0;
        }
        
        i++;
    }
    max2nd(chr_c, chr_i, num);
    // output the alphabet numbers in order.
    // for(int i=0; i<num; i++){
    //     cout<<chr_c[i]<<" ";
    // }
    // cout<<endl;
    // for(int i=0; i<num; i++){
    //     cout<<chr_i[i]<<" ";
    // }
    delete[] chr_c;
    delete[] chr_i;

}

int main() {
    const int bufferSize = 500; 
    char* chr = new char[bufferSize];
    cin >> chr;
    
    int num=0;
    while(chr[num]!='\0'){
        num++;
    }
    //cout<<num<<endl;

    //cout << chr << endl;
    countalphabet(chr, num);

    delete[] chr;
    return 0;
}
