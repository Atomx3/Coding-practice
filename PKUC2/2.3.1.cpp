#include <iostream>
#include <string>
#include <sstream>
using namespace std;
/*
编程题＃1：单词翻转
recursive function
cin.getline()
keep the original order of words, just reverse the order of letters of each word.
*/
// reverse Word function 
string reverseWord(string str) {
    if(str.empty()) {
        return "";
    }
    else {
        return reverseWord(str.substr(1)) + str[0];
    }
}

int main() {
    // char type is easy for input, but can not manipulate the space or tab
    char sentence[501];
    // input sentence string continuously
    while(cin.getline(sentence, 500) && sentence[0]!='\0'){
        sentence[500] = '\0'; // Ensure the sentence is null-terminated
// string initialized with the value of sentence, change datytype from char for easier to manipulate space.
        string str(sentence);
        size_t pos = 0;//pos is also the length of a sub string, count from 0
        //countinuly find the first position of space
        while ((pos = str.find_first_of(" \t")) != string::npos) {
            //find the first word(sub str) from begining of string to the beining of space.
            string word = str.substr(0, pos);
            cout << reverseWord(word);
            str = str.substr(pos);// a sbu string starts from the begin position of space. 
            size_t space_pos = str.find_first_not_of(" \t");// find the begin position of next word
            if (space_pos != string::npos) { // if the position of next word is not empty
                cout << str.substr(0, space_pos);// output the space in original length between words 
                str = str.substr(space_pos);// find next word.
            } 
            else {
                cout << str;
                str = "";
            }
        }
        cout << reverseWord(str) << endl;
    }
    return 0;
}