#include <iostream>
using namespace std;

/*
2. C程序设计进阶
3. 第三 module
3. 编程题＃3：排队游戏
*/

char boy;

// Recursive function to find pairs, start from a boy index.
int find_pair(char *queue, int start)
{
    // If we've reached the end of the string, return
    if (queue[start] == '\0') {
        return start;
    }

    // If the current character is a boy, find the next girl
    if (queue[start] == boy) {
        int boyIndex = start;
        int girlIndex = find_pair(queue, start + 1);
        if (queue[girlIndex] != boy) {
            cout << boyIndex << " " << girlIndex << endl;
            queue[boyIndex] = '0';
            queue[girlIndex] = '0';
        }
        return find_pair(queue, girlIndex + 1);
    }

    // If the current character is a girl, just return the index
    return start;
}

// 最简短的算法实现：
// 如果str[start]是男生，则match返回与之匹配的女生的序号
// 如果str[start]是女生，则返回该女生序号

// int match(char str[], int start)
// {
// 	if (str[start] != boy)
// 	{
// 		return start;
// 	}
// 	else
// 	{
// 		int boyIndex = start;
// 		int girlIndex = match(str, start + 1);
// 		cout << boyIndex << " " << girlIndex << endl;

// 		return match(str, girlIndex + 1);
// 	}
// }

int main()
{
    char queue[100];
    cin >> queue;
    boy = queue[0];
    find_pair(queue, 0);
    return 0;
}


/*
example
the input character could be any style of pair, 
such as <>, {}, [], but in an array, 
there is only one style, ()could be a pair,
but )( is not a pair, such as below.

input ((()(())())(()))
((()((Ab))cdA())(()))
output
2 3
5 6
4 7
8 9
1 10
12 13
11 14
0 15

input <<><><<<>>><<<><>>><>>
output 
1 2
3 4
7 8
6 9
5 10
13 14
15 16
12 17
11 18
19 20
0 21

char boy;

采用循环和递归的方法，有待实现
// remove the pairs from the queue array.
int find_pair(char *queue)
{
    char boy=queue[0];

    // set each pair value by ascii that queue[i] < queue[j].
    int i = 0, j=i+1;
    while(i<100){
        // find pairs and set empty flag = '0' in the array;
        if(queue[i] == boy && queue[j]!= boy){
            cout<< i <<" "<< j <<endl;
            queue[i]= '0';
            queue[j]= '0';
            i=j+1;
        }
        if((queue[i]!=boy && queue[j]==boy)
            || queue[i]==queue[j]|| queue[i]=='0'){
            i++;
        }
        if (queue[j]=='0'){
            j++;
        }
    }

    while(queue[i]!='0' && i <100){
        find_pair(queue);
        i++;
    }
    return 0;
}


*/
