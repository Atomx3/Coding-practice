/*
1. 计算导论与C语言基础，系列第1课  
7. 理性认识C程序 导论，第7周  
2.3 编程题＃3：找出第k大的数

注意： 总时间限制: 1000ms 内存限制: 65536kB

描述
用户输入N和K，然后接着输入N个正整数（无序的），程序在不对N个整数排序的情况下，找出第K大的数。注意，第K大的数意味着从大到小排在第K位的数。

输入
N

K

a1 a2 a3 a4 ..... aN

输出
b

样例输入
5
2
32 3 12 5 89
样例输出
32

提示  
这是一道很经典的算法问题，是公司面试的常见考题。以后学习递归之后再回头看看这道题，或许有新解法。

解決方案2: 快速選擇算法 Quickselect
不对整个数组进行排序的情况下，可以高效地找到第K大的数。

*/

#include <iostream>
using namespace std;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function used in Quickselect
int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left;
    for (int j = left; j < right; j++) {
        if (arr[j] > pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}

// Quickselect function to find the k-th largest element
int quickselect(int arr[], int left, int right, int k) {
    if (left == right) {
        return arr[left];
    }
    int pivotIndex = partition(arr, left, right);
    if (k == pivotIndex) {
        return arr[k];
    } else if (k < pivotIndex) {
        return quickselect(arr, left, pivotIndex - 1, k);
    } else {
        return quickselect(arr, pivotIndex + 1, right, k);
    }
}

int main() {
    int n, k;
    cin >> n >> k;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // Find the k-th largest element
    int result = quickselect(a, 0, n - 1, k - 1);
    cout << result << endl;

    return 0;
}


   