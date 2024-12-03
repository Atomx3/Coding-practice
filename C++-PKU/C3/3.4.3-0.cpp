/*
3. C++程序设计
4. 第4周
3. 编程题＃3：


this solution could not pass the test of old version of coursera examination.

Debug 分析
若输出结果末尾有类似以下malloc错误提示，则为内存管理故障
a.out(9985,0x116cb5600) malloc: *** error for object 0x5390eb981100: pointer being freed was not allocated
a.out(9985,0x116cb5600) malloc: *** set a breakpoint in malloc_error_break to debug
zsh: abort      ./a.out

因为对象a赋值给另一个对象b，缺少赋值运算符重载Array2& operator=()，
而编译器生成的默认赋值运算符只会进行浅拷贝（shallow copy），
它只会复制arr指针本身，而不会复制arr指向的内存。
这就导致了a和b实际上指向了同一块内存，析构函数（~Array2()）被调用时，
它们都会试图删除同一块内存，导致以上malloc错误提示

因此需要定义一个赋值运算符，进行深拷贝（deep copy）。
深拷贝会复制arr指向的内存，而不仅仅是arr指针本身。
这样，a和b就会有各自独立的内存，互不影响。

*/

#include <iostream>
using namespace std;

class Array2 {
  private:
    int** arr;
    int row;
    int col;

  public:
    // this constructor is for object b without argument.
    // Default constructor has no parameter or default parameters
    Array2() : row(0), col(0), arr(nullptr) {}
    // constructor
    Array2(int r, int c) {
        row = r;
        col = c;
        // dynamically allocate memory for array.
        arr = new int*[row];
        for (int i = 0; i < row; i++) {
        arr[i] = new int[col]; 
        }
    }
    // assignment operator
    Array2& operator=(const Array2& other) {
      if (this != &other) { // prevent self assigment
          // delete original memory
          for (int i = 0; i < row; i++) {
              delete[] arr[i];
          }
          delete[] arr;

          // copy the numbers of row and colum 
          row = other.row;
          col = other.col;

          // allocate new memory and copy data
          arr = new int*[row];
          for (int i = 0; i < row; i++) {
              arr[i] = new int[col];
              for (int j = 0; j < col; j++) {
                  arr[i][j] = other.arr[i][j];
              }
          }
      }
      return *this;
    }
    ~Array2() {
      for (int i = 0; i < row; i++) {
        delete[] arr[i]; 
      }
      delete[] arr;
    }
    // overload operator, return pointer.
    int* operator[](int i) {
      return arr[i]; 
    }
    //operator()could accept more arguments, more flexible.
    //2D index operator[] is not allow to overload in c++.
    int operator()(int i, int j) {
      return arr[i][j];
    }
};

int main() {

  Array2 a(3,4);
  int i, j;

  // Set values
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      a[i][j] = i*4 + j;
    }
  }

  // Print values
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cout << a(i,j) << ","; 
    }
    cout << endl;
  }
  
  cout << "next" << endl;

  // Copy array
  Array2 b; b = a ; 
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      b[i][j] = a[i][j];
    }
  }

  // Print copy
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      cout << b(i,j) << ",";
    }
    cout << endl;
  }

  return 0;
}
