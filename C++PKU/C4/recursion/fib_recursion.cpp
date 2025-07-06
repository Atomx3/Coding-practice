#include <iostream>

// 原始递归版本
int fib_recursive(int n) {
    if (n <= 1) return n;
    return fib_recursive(n - 1) + fib_recursive(n - 2);
}

// 简单测试
int main() {
    std::cout << "Fibonacci Recursive Implementation:\n";
    
    for (int i = 0; i <= 10; ++i) {
        std::cout << "F(" << i << ") = " << fib_recursive(i) << "\n";
    }
    
    return 0;
}
