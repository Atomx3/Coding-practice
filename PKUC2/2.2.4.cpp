#include <iostream>
#include <iomanip>
using namespace std;

/*
编程题＃4：Tomorrow never knows？
calculate the next day when input a date

*/



// define the days of each month of leap year in an array.
int days_leap[12]={31,29,31,30,31,30,31,31,30,31,30,31};
int y=0, m=0, d=0;
char dash=' ';

int date(int y, int m, int d){
    // if it is a leap year
    if((y%4==0 && y%100!=0)||(y%400==0)){
        // add one more day
        if(d< days_leap[m-1])
        {   d+=1;}
       
        // add one more month
        else if((m<12 && d== days_leap[m-1])||d==days_leap[m-1]){
                m+=1;
                d=1;
            }
     
        // add one more year
        else if(m==12 && d== days_leap[m-1])
        {   y+=1;
            m=1;
            d=1;}

    // if it is not a leap year
    }
    else{
        // add one more day
        if(d< days_leap[m-1]-1)
        {   d+=1;}
  
        // add one more month
        else if( (m==2 && d==days_leap[m-1]-1) ||d==days_leap[m-1]) {
                m+=1;
                d=1;
            }
     
        // add one more year
        else if(m==12 && d==days_leap[m-1])
        {   y+=1;
            m=1;
            d=1;}
    
    }       
    // set fill char and width by <iomanip>.
    cout<<y<<dash<<setfill('0')<<setw(2)<<m<<dash<<setfill('0')<<setw(2)<<d<<endl;
    
    return 0;


}




int main()
{
// input the date y-m-d;    

while(cin>>y>>dash>>m>>dash>>d){
    // warn users to input right date.
    if((y<1600||y>2999)||(m<1||m>12)
    || (d<1 || d>days_leap[m-1]) ){
    //    cout<<"please input right date"<<endl;
    //    cout<<"1600<= year <=2999"<<endl;
        continue;
    }
    // output the original date y-m-d; 
    //cout<<y<<dash<<m<<dash<<d<<endl;

    // output the date y-m-d; 
    date(y,m,d);

}

    return 0;   
}

/*
example data
input 

*/