#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    // input patients number n
    int n=0;
    cin>>n;

    // input the patients age into array
    int age[n];
    for(int i=0; i<n; i++){
        cin>>age[i]; 
    }

    // count the numbers of each age group;
    int age18l =0, age35l=0, age60l=0, age60m=0;
    for(int i=0; i<n; i++){

        if(age[i] <=18 ){ age18l ++;}
        else if(age[i]>=19 && age[i]<=35){age35l++;}
        else if (age[i]>=36 && age[i]<=60){age60l++;}
        else {age60m ++;}
        
        }
    
    double age18lr= (double)age18l/n *100 ;
    double age35lr= (double)age35l/n *100 ;
    double age60lr= (double)age60l/n *100 ;
    double age60mr= (double)age60m/n *100;
    
    // output the rate of each age group.
    // std::cout<<"1-18:"<< std::fixed<< std::setprecision(2)<<age18lr<<"%"<<std::endl;
    // printf("1-18: %.2f %%\n",age18lr);  
    // printf("19-35: %.2f %%\n",age35lr);  
    // printf("36-60: %.2f %%\n",age60lr);  
    // printf("60-: %.2f %%\n",age60mr);

    cout<<"1-18: "<<fixed<<setprecision(2) << age18lr<<"%"<<endl;   
    cout<<"19-35: "<<fixed<<setprecision(2) << age35lr<<"%"<<endl;   
    cout<<"36-60: "<<fixed<<setprecision(2) << age60lr<<"%"<<endl;   
    cout<<"60-: "<<fixed<<setprecision(2) << age60mr<<"%"<<endl;   


    return 0;
    }
    

   