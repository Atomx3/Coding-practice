#include <iostream>
#include <stack>

// 方法1：使用Frame结构体的栈模拟递归（推荐）
struct Frame {
    int n;
    int stage;  // 0: 初始, 1: 已计算F(n-1), 2: 完成
    int fib_n_1; // 存储F(n-1)的结果
    
    // 添加构造函数以支持旧版本C++
    Frame(int n_val, int stage_val, int fib_n_1_val) 
        : n(n_val), stage(stage_val), fib_n_1(fib_n_1_val) {}
};

int fib_stack_frame(int n) {
    if (n <= 1) return n;
    
    std::stack<Frame> call_stack;
    std::stack<int> result_stack;
    
    call_stack.push(Frame(n, 0, 0));
    
    while (!call_stack.empty()) {
        Frame& current = call_stack.top();
        
        if (current.n <= 1) {
            // 基础情况
            result_stack.push(current.n);
            call_stack.pop();
        }
        else if (current.stage == 0) {
            // 需要计算F(n-1)
            current.stage = 1;
            call_stack.push(Frame(current.n - 1, 0, 0));
        }
        else if (current.stage == 1) {
            // F(n-1)已计算完，获取结果并计算F(n-2)
            current.fib_n_1 = result_stack.top();
            result_stack.pop();
            current.stage = 2;
            call_stack.push(Frame(current.n - 2, 0, 0));
        }
        else { // stage == 2
            // F(n-2)已计算完，合并结果
            int fib_n_2 = result_stack.top();
            result_stack.pop();
            result_stack.push(current.fib_n_1 + fib_n_2);
            call_stack.pop();
        }
    }
    
    return result_stack.top();
}

// 方法2：使用两个栈的简化版本
int fib_stack_two_stacks(int n) {
    if (n <= 1) return n;
    
    std::stack<int> work_stack;
    std::stack<int> result_stack;
    
    work_stack.push(n);
    work_stack.push(-1); // 标记开始
    
    while (!work_stack.empty()) {
        int current = work_stack.top();
        work_stack.pop();
        
        if (current == -1) {
            // 标记，表示需要合并两个结果
            if (result_stack.size() >= 2) {
                int b = result_stack.top(); result_stack.pop();
                int a = result_stack.top(); result_stack.pop();
                result_stack.push(a + b);
            }
        }
        else if (current <= 1) {
            result_stack.push(current);
        }
        else {
            // 需要计算F(n-1)和F(n-2)
            work_stack.push(-1); // 合并标记
            work_stack.push(current - 1);
            work_stack.push(current - 2);
        }
    }
    
    return result_stack.top();
}

// 简单测试
int main() {
    std::cout << "Fibonacci Stack Simulation Implementation:\n";
    std::cout << "Method 1 (Frame struct):\n";
    
    for (int i = 0; i <= 10; ++i) {
        std::cout << "F(" << i << ") = " << fib_stack_frame(i) << "\n";
    }
    
    std::cout << "\nMethod 2 (Two stacks):\n";
    for (int i = 0; i <= 10; ++i) {
        std::cout << "F(" << i << ") = " << fib_stack_two_stacks(i) << "\n";
    }
    
    return 0;
}
