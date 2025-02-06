#include <iostream>
using namespace std;
int main() {
    // input k and array;
    int k, a ;
    cin >> k;
    
    
    int count1=0, count5=0, count10=0;
    for (int i=0; i<k; i++) {
        cin >> a;
        //count number i
        if (a == 1 )count1++;
        else if (a == 5)count5++;
        else if (a == 10)count10++;

    }
    // ouput the result
    cout << count1 << endl;
    cout << count5 << endl;
    cout << count10 << endl;
    
    return 0;
}
//其实还有更快的算法你能想到吗？