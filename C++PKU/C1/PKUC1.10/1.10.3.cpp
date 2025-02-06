/*
1. 计算导论与C语言基础，系列第1课  
10. 理性认识C程序 导论，第10周  
3. 编程题＃3：最长单词2

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
一个以'.'结尾的简单英文句子，单词之间用空格分隔，没有缩写形式和其它特殊形式

输入
一个以'.'结尾的简单英文句子（长度不超过500），单词之间用空格分隔，没有缩写形式和其它特殊形式

输出
该句子中最长的单词。如果多于一个，则输出第一个

样例输入
第一组
I am a student of Peking University.
第二组
Hello world.

样例输出
第一组
University
第二组
Hello

*/

#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // Input sentence to array with the end of symbol '.'.
    char str[500] = {0};
    cin.getline(str, 500);

    // Sorting words from str[] to another array str_word[].
    int j = 0, i = 0, word_index = 0;
    char str_word[500][500] = {0};

    while (i < strlen(str)) {
        if (str[i] == ' ' || str[i] == '.') {
            str_word[j][word_index] = '\0';
            word_index = 0;
            j++;
        } else {
            str_word[j][word_index] = str[i];
            word_index++;
        }
        i++;
    }
    str_word[j][word_index] = '\0';

    // Output the largest word's numbers.
    int k = 0, maxNum = 0, maxIndex = 0;
    while (k <= j && str_word[k][0] != '\0') {
        int q = 0;
        while (str_word[k][q] != '\0') {
            q++;
        }
        if (q > maxNum) {
            maxNum = q;
            maxIndex = k;
        }
        k++;
    }

    // Output the largest word.
    cout << str_word[maxIndex] << endl;

    return 0;
}
