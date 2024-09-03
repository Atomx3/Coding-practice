#include <stdlib.h>
// Interacting with the System and Managing Memory, Duke University
// coursera, Module 2, lesson 6 Valgrind

// check valgrind-memcheck.md

// error reports, by below section of code
  void f(void)
  {
     int* x = malloc(10 * sizeof(int));
     x[10] = 0;        // problem 1: heap block overrun
  }                    // problem 2: memory leak -- x not freed


// fix the above problem
// void f(void)
// {
//    int* x = malloc(10 * sizeof(int));
//    if (x != NULL) {
//       x[9] = 0;  // Accessing the last valid element
//       free(x);   // Freeing the allocated memory
//    }
// }

  int main(void)
  {
     f();
     return 0;
  }
