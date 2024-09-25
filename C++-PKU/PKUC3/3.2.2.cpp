/*
3. C++程序设计
2. 第2周
2. 简单的学生信息处理程序实现

I input k numbers of words, there is a comma "," to seperate two chars, no extra space.
each word has maximum n numbers of chars.
please use c++, 2D array pointers to store the words without comma and space.
then output the words line by line. 

*/

#include <iostream>
#include <cstring> // for strtok
using namespace std;

void scores(int n, char **words) {
    // words[0] = char name[10], words[1] = int age; words[2] = char id[10]; 
    // words[3]~[6] = score1[10], score2[10], score3[10], score4[10];

    int ave_scores = 0;
    // stoi, convert string to int.
    ave_scores = (stoi(words[3]) + stoi(words[4]) + stoi(words[5]) + stoi(words[6])) / 4;
    cout << words[0] << "," << words[1] << "," << words[2];
    cout << "," << ave_scores << endl;
}

int main() {
    const int k = 10; // Maximum number of characters per word
    const int n = 7; // Maximum number of words

    char input[n * (k + 1)]; // +1 for null terminator
    cin.getline(input, sizeof(input));

    // Parse the input and store words in a 2D array of pointers
    char* words[n];
    int wordCount = 0;

    char* token = strtok(input, ",");
    while (token != nullptr && wordCount < n) {
        // Allocate memory for the word
        words[wordCount] = new char[strlen(token) + 1]; // +1 for null terminator
        strcpy(words[wordCount], token);

        wordCount++;
        token = strtok(nullptr, ",");
    }

    // Output the whole information line by line
    // for (int i = 0; i < wordCount; ++i) {
    //     cout << words[i] << endl;
    // }

    // Calculate and output the average score
    scores(n, words);

    // Deallocate memory
    for (int i = 0; i < wordCount; ++i) {
        delete[] words[i];
    }

    return 0;
}
