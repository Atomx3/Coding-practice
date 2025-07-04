/*
2. C程序设计进阶
9. 第9 module
5. 编程题＃5：走出迷宫
5 6
S . . . . T
. # . . # .
. . . # . .
. # . . . #
. . . # . .
output it's shortest steps(integer).


please design a c++ program, to find the shortest path from the entrance to the exit of a maze.
Description: the maze is a 2D array, char pointers, n rows and m colum.
it's entrance symble is 'S', and exit symble is 'T'. 
the other elements(points) of the array has two kinds of char.
char '.' means available path to pass, char '#' means wall that block the path.
each point has x and y as coordination, such as maze[x][y] is a point.
your each step could only move along colum(Vertical) or row(horizontal), so you could only move step to '.' char, you are blocked by '#' char . 
output the shortest path in the form of another 2D array of integers with elements of x and y from maze[x][y]. 

*/
#include <iostream>
using namespace std;

void path(int n, int m, char **maze){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(maze[i][j]== 'S'){
                while(maze[i][j]!='T'){
                    // prefer walk by x coordinate;
                    if(maze[i][j+1]!='#'){
                        j++;
                    }
                    else if(maze[i+1][j]!='#'){
                        i++;
                    }
                    else if{
                        
                    }
                    
                }
            }
            // else{
            //     cout<<"Error: no entrance"<<endl;
            //     return;
            // } 
        }
    }
}

int main(){
    int n=0, m=0;
    while(true){
        cin>>n>>m;
        if(n>=1 && m<=100){
            break;// Exit the loop if valid input
        }
        else{
            cout<<"wrong input again!"<<endl;
        }
    }

    char **maze= new char*[n];
    for(int i=0; i<n; i++){
        maze[i]= new char[m];
        cin>>maze[i];
    }

    // for(int i=0; i<n; i++){
    //     cout<<maze[i]<<endl;
    // }
    path(n,m,maze);
    for(int i=0; i<n; i++){
        delete[] maze[i];
    }
    delete[] maze;

    return 0;   
}