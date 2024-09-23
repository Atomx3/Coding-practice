/*
1. 计算导论与C语言基础，系列第1课  
7. 理性认识C程序 导论，第7周  
2.3 编程题＃3：找出第k大的数

解決方案1: 通过排序来找到第K大的数
但題目要求不用排序法。

*/

#include <iostream>
using namespace std;

void swap (int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

// sorting from big to small.
void bubble_sort (int arr [], int size) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr [j] < arr [j + 1]) {
        swap (arr [j], arr [j + 1]);
      }
    }
  }
}



// find the kth biggest number.
int kth_largest(int n, int k, int a[]) {
// to skip over duplicate values in a[n]
  bubble_sort(a, n);
    int count = 1;
    for (int i = 1; i < n ; i++) {
        if (a[i] != a[i - 1]) {count++;} 
        else if (count == k) {return a[i];}}
    return a[k+count-2];}

int main() {
// input n, k, a[].
int n=0, k=0;
cin>>n;
cin>>k;
int a[n];
for(int i=0; i<n; i++){
    cin>>a[i];
};
// print out the array before sorting
// for (int i = 0; i < n; i++) {
// cout << a[i] << " ";}
// cout << endl;

// print the array after sorting.
//bubble_sort(a,n);
//for (int i = 0; i < n; i++) {
//  cout << a [i] <<" ";}
//  cout<< "" << endl;


// output the final result
cout<<kth_largest(n,k,a)<<endl;

return 0;
    }
