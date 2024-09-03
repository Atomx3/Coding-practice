# Duke- C3w3- Multidimensional Arrays

Incompatible Representations
C语言中多维数组中不兼容表示
参考更多案例：

github/c3w3_1.segmentation_fault.c

github/c3w3_1.compiler_wrong.c

```c
#include <stdio.h>

void printArray(int (*arr)[5], int rows) {
	for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < 5; ++j) {
				printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}
int main() {
	int twoDArray[3][5] = {
		{1, 2, 3, 4, 5},
		{6, 7, 8, 9, 10},
		{11, 12, 13, 14, 15}
	};
	// 这将有效，因为函数期望一个指向包含5个整数的数组的指针
		printArray(twoDArray, 3);

	return 0;
}
```