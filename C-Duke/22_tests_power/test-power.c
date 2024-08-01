#include <stdio.h>
#include <stdlib.h>

// power函数的原型
unsigned power(unsigned x, unsigned y);

// 辅助函数，用于运行单个测试用例
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
    unsigned result = power(x, y);
    if (result != expected_ans) {
        printf("Failed: power(%u, %u) returned %u, expected %u\\n", x, y, result, expected_ans);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    // 测试用例
    run_check(0, 0, 1); // 边界情况：0的0次方通常被视为1
    run_check(2, 3, 8); // 常规情况：2的3次方等于8
    run_check(10, 0, 1); // 任何数的0次方应该是1
    run_check(0, 5, 0); // 0的任何次方应该是0
    run_check(1, 1, 1); // 1的任何次方应该是1
    run_check(2, 31, 2147483648U); // 大数情况：2的31次方，测试类型错误
    run_check(2, 32, 0); // 2^32 exceeds the range of unsigned int, expect 0 due to overflow

    // 添加更多测试用例以覆盖不同的情况

    // Additional test cases
run_check(2, 1, 2); // Simple case: 2^1 should return 2
run_check(1, 2, 1); // Simple case: 1^2 should return 1
run_check(2, 16, 65536); // 2^16 should return 65536
run_check(2, 15, 32768); // 2^15 should return 32768
run_check(4294967295, 1, 4294967295); // Max unsigned int to the power of 1
run_check(2, 30, 1073741824); // 2^30 should return 1073741824


    // 如果所有测试通过
    printf("All test cases passed!\\n");
    exit(EXIT_SUCCESS);
}

