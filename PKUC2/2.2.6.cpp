#include <iostream>
#include <iomanip>

using namespace std;

/*
编程题＃6：流感传染
flu bacteria contamination model
细菌扩散模型，每天一次，向外扩展，仅污染一层邻居。
Once a day, expand outward to contaminate only one layer of neighbors.
*/

// make function for the model
void cont(int n, char a[100][100], int m){
    //store the sick coordinate data in the array sick[sick_Index][2].
    int sick_Index=0;
    int sick[100][2]={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(a[i][j]=='@'){ 
                // the first day, original sick data coordinate.
                //cout<<setw(2)<<i<<setw(2)<<j<<endl; 
                sick[sick_Index][0]=i;
                sick[sick_Index][1]=j;
                sick_Index++;      
            }         
        }
    }
    //output the sick data coordinate by array sick[][2].
    //for(int q=0;q<sick_Index;q++){  
    //cout<<setw(2)<<sick[q][0]<<setw(2)<<sick[q][1]<<endl;}

    // execute contamination model 
    for(int day=2; day<=m;day++){
        // calculate the contamination in a specific days m.
        // control or stop contamination to whole cells on the second day.
        int new_sick_Index=0,new_sick[100][2]={0};
        for(int q=0;q<sick_Index;q++){
            int i=sick[q][0];
            int j=sick[q][1];
            if(i>0 && a[i-1][j]== '.'){
                a[i-1][j]= '@';
                new_sick[new_sick_Index][0]=i-1;
                new_sick[new_sick_Index][1]=j;
                new_sick_Index++;   
            } 
            if(j>0 && a[i][j-1]== '.'){
                a[i][j-1]= '@';
                new_sick[new_sick_Index][0]=i;
                new_sick[new_sick_Index][1]=j-1;
                new_sick_Index++; 
            }
            if(j<n-1 && a[i][j+1]== '.'){
                a[i][j+1]= '@';
                new_sick[new_sick_Index][0]=i;
                new_sick[new_sick_Index][1]=j+1;
                new_sick_Index++; 
            }
            if(i<n-1 && a[i+1][j]== '.'){
                a[i+1][j]= '@';
                new_sick[new_sick_Index][0]=i+1;
                new_sick[new_sick_Index][1]=j;
                new_sick_Index++; 
            }
        }
        // Add newly_sick cells to sick array
        for(int i=0; i<new_sick_Index; i++){
            sick[sick_Index][0] = new_sick[i][0];
            sick[sick_Index][1] = new_sick[i][1];
            sick_Index++;
        }

    }
    // output the sick map(array) after being contaiminated in a specific m days.
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<setw(2)<<a[i][j];
        }
        cout<<endl;
    }
    cout<<sick_Index<<endl;
 
}


/*
// contamination model 2.
void flu(int n, char a[100][100], int m){
    
    int num_Health=0, num_Sick=0, num_Empt=0;
    //output the original array.
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<setw(2)<<a[i][j];
        }
        cout<<endl;
    }

    // calculate and output number of each kind of situation
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            switch(a[i][j]){
                case '.':
                num_Health++;
                break;
                case '@':
                num_Sick++;
                break;
                case '#':
                num_Empt++;
                break;
            }
        }
    }
    //cout<<setw(2)<<num_Health<<setw(2)<<num_Sick<<setw(2)<<num_Empt<<endl;

    //    cont(n,a,m);

}     
*/
   

int main(){
    // input data to array.
    int n=0, m=0;
    cin>>n;
    char a[100][100]={0};
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    cin>>m;

    // calculate by function 
    cont(n, a, m);


    return 0;   

}



/*
example data
input 
5
....#
.#.@.
.#@..
#....
.....
1-4

7
....#@.
.#.@..#
.#@....
#....@#
.......
#....@#
.......
1-7

*/
