# Duke- C3w1- Read pointer1

Date: December 10, 2023

**C pointer**

[C语言指针详解，30分钟玩转C语言指针 (biancheng.net)](https://c.biancheng.net/c/80/)

[C语言指针变量的定义和使用（精华）_54笨鸟 (54benniao.com)](https://www.54benniao.com/c/pointer/)

```c
#include <stdio.h>
#include <stdlib.h>

void g(int x, int * y) {
printf("In g, x = %d, *y = %d\n", x, *y);
x++;
*y = *y - x;
y = &x;
}

void f(int * a, int b) {
printf("In f, *a = %d, b = %d\n", *a, b);
*a += b;
b *= 2; // * multiply, not pointer identifier here;
g(*a, &b);
printf("Back in f, *a = %d, b = %d\n", *a, b);
}

int main(void) {
int x = 3;
int y = 4;
f(&x, y);
printf("In main: x = %d, y = %d\n", x, y);
return EXIT_SUCCESS;
}
```

## Output

In f, *a = 3, b = 4
In g, x = 7, *y = 8
Back in f, *a = 7, b = 0
In main: x = 7, y = 4

**execute the code by hand and write the output.**

## Why? Back in f, *a = 7, b = 0

g(*a, &b) = (7, 8)

&b means, the first address of the value 8, so b =0;

**Swap with Hardware**

[how pointers work?](https://www.coursera.org/learn/pointers-arrays-recursion/lecture/KyCkQ/swap-with-hardware)

`int *y, y = &x;`

what’s `y, x, *y, &x` difference in the above program?

 Pointers symbols: `*, &` 

dereference the arrow? 

**the `*` operator**, dereferences a pointer (follows an arrow), 

**the `&` operator**, takes the address of something (gives an arrow pointing at that thing).

**shorthand** for dereferencing a pointer to a struct and selecting a field

`(**q*)*.x = q->x*`

`*(*(*(*q).r).s).t. = q->r->s->t*`