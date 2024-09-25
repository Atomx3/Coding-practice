/*
2. C程序设计进阶
5. 第五周
3. 编程题＃3：文字排版
c++ program, 

input: a sentence with k numbers of words(strings), 
each word has 40 numbers of characters by ascii table. 
and may include punctuation characters immediately before or after it.
a space between two words.

output: 
seperate the whole sentence, and output every line of sentence within 80 characters, 
including space, words and punctuation characters. 
there is no space before or after each line of sentence. 

eg. 
input
% ./a.out | cat -e 
84
One sweltering day, I was scooping ice cream into cones and told my four children they could "buy" a cone from me for a hug. Almost immediately, the kids lined up to make their purchases. The three youngest each gave me a quick hug, grabbed their cones and raced back outside. But when my teenage son at the end of the line finally got his turn to "buy" his ice cream, he gave me two hugs. "Keep the changes," he said with a smile.

output
One sweltering day, I was scooping ice cream into cones and told my four$
children they could "buy" a cone from me for a hug. Almost immediately, the kids$
lined up to make their purchases. The three youngest each gave me a quick hug,$
grabbed their cones and raced back outside. But when my teenage son at the end$
of the line finally got his turn to "buy" his ice cream, he gave me two hugs.$
"Keep the changes," he said with a smile.%  

*/
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	int num = 0, lineLength = 0;
	cin >> num;
	char word[40];
	for (int i = 0; i < num; i++)
	{
		cin >> word;
		if (lineLength + strlen(word) + 1> 80)
		{
			cout << endl;
			lineLength = 0;
		}
		else if (lineLength > 0)
		{
			cout << " ";
			lineLength++;
		}
		cout << word;
		lineLength += strlen(word);
	}
	return 0;
}


/*

// output the new paragraph.
void paragraph(char *sentence, int *charNum, int k){
    int i=0, length=0, q=0, charTotal=0;
    
        while(sentence[q]!='\0'){
            
            while(length -1 <=80 && i<k){
                length+=charNum[i]+1;
                i++; 
            }
            charTotal += length-1 ;
            if(q <= charTotal ){
                cout<<sentence[q];
                q++;
            }
            q=length+1;
            length=0;
            cout<< endl;

        }
}

void sortWord(char *sentence, int k){
    char* word = new char[40];  // Allocate memory for each word within 40 bytes
    int* charNum= new int[k];
    
    stringstream ss(sentence);
    int i=0;
    while(ss >> word && i<k) {
        // i = wordCount = 0, ++wordCount;
        charNum[i]=strlen(word);
        if(strlen(word) > 40) {
            cout << "Invalid input. lenth<= 40.\n";
            //delete[] sentence;
            delete[] word;
            delete[] charNum;
            return;
        }
        i++;
    }

    if(i != k) {
        cout << "Invalid input \n";
        delete[] word;
        delete[] charNum;
        return;
    }
    
    paragraph(sentence, charNum, k);
    delete[] word;
    delete[] charNum;
}

int main() {
    int k;
    cin >> k;
    cin.ignore();  // To ignore the newline character after entering k
    char* sentence = new char[41*k]; // Allocate memory for the sentence, space count for 1 byte
    cin.getline(sentence, 41*k);

    sortWord(sentence, k);
    delete[] sentence;  // Delete the allocated memory

    return 0;
}

//string automatically deal with memory, don't need pointer.
int main() {
    int k;
    cin >> k;
    cin.ignore(); 
    string sentence;
    getline(cin, sentence);
    stringstream ss(sentence);
    string words;
    int wordCount=0;
    while(ss>>words){
        wordCount++;
        if(words.length()>40){
            cout<<"word must be less than 40"<<endl;
            return 0;
        }
    }
    if(wordCount!=k){
        cout<<"check words numbers"<<'\n';
        return 0;
    }

    cout << sentence << '\n';
    return 0;
}
*/