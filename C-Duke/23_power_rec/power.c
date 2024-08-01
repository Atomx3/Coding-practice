// power.c
#include <stdio.h>

// Recursive function to compute x to the y power
unsigned power(unsigned x, unsigned y) {
    // Special case: 0^0 is defined as 1
    if (x == 0 && y == 0) {
        return 1;
    }
    // Base case: x to the power of 0 is 1
    if (y == 0) {
        return 1;
    }
    // Recursive step: x^y = x * x^(y-1)
    return x * power(x, y - 1);
}

