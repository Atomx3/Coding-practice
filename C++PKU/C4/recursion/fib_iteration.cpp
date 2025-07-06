#include <iostream>

// 迭代版本
int fib_iter(int n) {
    if (n <= 1) return n;
    
    int a = 0, b = 1, result = 0;
    
    for (int i = 2; i <= n; ++i) {
        result = a + b;
        a = b;
        b = result;
    }
    
    return result;
}

// 简单测试
int main() {
    std::cout << "Fibonacci Iterative Implementation:\n";
    
    for (int i = 0; i <= 20; ++i) {
        std::cout << "F(" << i << ") = " << fib_iter(i) << "\n";
    }
    
    return 0;
}

