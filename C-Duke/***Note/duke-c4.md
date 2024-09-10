
### Interacting with the System and Managing Memory 
### Duke University, Course 4


# Module 1: Interacting with user and System


## the Operating System

printf(library call)  uses the write(system call).

Novice programmers are often imprecise about the difference between a system call (which transfers control into the OS, requesting it to perform a task), and a library call (which calls a function found in a library, such as the C standard library).

https://www.geeksforgeeks.org/difference-between-system-call-and-library-call/


## Command Line Arguments
```c 
int argc, char ** argv
```

## Complex Option Processing
get option character from command line argument list

```c
int getopt(int argc, char * const argv[], const char *optstring);
```


## The Environment Pointer
`main` can potentially take a third argument: environment variable functions.

```c
 #include <stdlib.h>

     char *
     getenv(const char *name);

     int
     setenv(const char *name, const char *value, int overwrite);

     int
     putenv(char *string);

     int
     unsetenv(const char *name);
```

# Module 2: Dynamic allocation

most of the memory we have used has been located on the stack. Dynamic memory allocation gives a programmer much more flexibility, in that it allows you to request a specific amount memory to be allocated on the heap, so that it will not disappear with the stack frame of the calling function.

## heap vs. stack

[Stack vs Heap: What's the difference? (educative.io)](https://www.educative.io/blog/stack-vs-heap)

### Stack

- **Memory Allocation**: Static memory allocation.
- **Usage**: Used for storing local variables, function parameters, and return addresses.
- **Lifetime**: Memory is automatically managed. It is allocated when a function is called and deallocated when the function returns.
- **Size**: Typically smaller and limited in size.
- **Speed**: Faster access due to its LIFO (Last In, First Out) nature.
- **Structure**: Organized in a contiguous block of memory.

### Heap

- **Memory Allocation**: Dynamic memory allocation.
- **Usage**: Used for allocating memory for data structures like linked lists, trees, and arrays whose size may not be known at compile time.
- **Lifetime**: Memory must be manually managed. It remains allocated until explicitly freed by the programmer.
- **Size**: Generally larger and can grow as needed.
- **Speed**: Slower access compared to the stack due to its more complex management.
- **Structure**: Organized in a more scattered manner, with memory blocks allocated as needed.

In summary, the stack is used for static memory allocation with automatic management, while the heap is used for dynamic memory allocation with manual management. Both have their own advantages and are used for different purposes in programming.

## Why malloc is named as dynamic allocation ?

### Stack Memory Allocation

- **Fixed Size**: The size of the stack is determined at compile time and is fixed. You cannot dynamically change the size of the memory allocated on the stack during the program’s execution.
- **Automatic Management**: The memory for local variables is automatically allocated when a function is called and deallocated when the function returns. This process is managed by the system and does not allow for resizing.

### Heap Memory Allocation

- **Dynamic Size**: The size of memory allocated on the heap can be determined and changed during the program’s execution. You can use functions like **`malloc()`**, **`calloc()`**, and **`realloc()`** to allocate and resize memory as needed.
- **Manual Management**: You have control over the allocation and deallocation of memory on the heap, allowing for more flexible and efficient memory management.

## **More Complex Structures**

```c
struct point_tag {
  int x;
  int y;
};
typedef struct point_tag point_t;

struct polygon_tag {
  size_t num_points;
  point_t * points;
};
typedef struct polygon_tag polygon_t;
 	
polygon_t * makeRectangle(point_t c1, point_t c2) {
  polygon_t * answer = malloc(sizeof(*answer));
  answer->num_points = 4;
  answer->points = malloc(
	  answer->num_points * sizeof(*answer->points));
  answer->points[0]   = c1;
  answer->points[1].x = c1.x;
  answer->points[1].y = c2.y;
  answer->points[2]   = c2;
  answer->points[3].x = c2.x;
  answer->points[3].y = c1.y;
  return answer;
}
```

### The right arrow mark **`->`**

 **`->`** operator is used to access members of a structure through a pointer, It is a shorthand for dereferencing a pointer and then accessing the member. 

making the code more concise and readable.

```c
polygon_t * answer = malloc(sizeof(*answer));
answer->num_points = 4;
answer->points = malloc(
	answer->num_points * sizeof(*answer->points));
```

- **`answer`** is a pointer to a **`polygon_t`** structure.
- **`answer->num_points`** is equivalent to **`(*answer).num_points`**. It accesses the **`num_points`** member of the **`polygon_t`** structure that **`answer`** points to.
- **`answer->points`** is equivalent to **`(*answer).points`**. It accesses the **`points`** member of the **`polygon_t`** structure that **`answer`** points to.

## free

Case1: the block of memory that you freed is deallocated, and you may no longer use it, pointers are dangling.

what’s the problem probably?

1. **Null Pointer Dereference**: If **`p`** or **`p->points`** is **`NULL`**, calling **`free(p->points)`** or **`free(p)`** may cause the program to crash or exhibit undefined behavior.
2. **Double Free**: If **`p->points`** or **`p`** has already been freed elsewhere, calling **`free`** again will result in a double free error, which may cause the program to crash or exhibit other undefined behavior.
3. **Memory Leak**: If memory is not properly freed in certain situations, it may lead to a memory leak, causing the program to consume more and more memory, eventually exhausting system resources.

```c
// if we don't check the pointers are null or not?  
polygon_t * p = makeRectangle(c1, c2);
//stuff that uses p
//...
//done with p and its points
free(p->points);
free(p);

// we improve above code as below
polygon_t * p = makeRectangle(c1, c2);
// 使用 p 的代码
//...
// 完成对 p 和其 points 的使用
if (p != NULL) {
if (p->points != NULL) {
free(p->points);
}
free(p);
}
```

Case2: This code **free**s a pointer not returned by malloc

```c
int xcount = 0;
char * ptr = malloc(50 * sizeof(char));
// Reading Input
if (fgets(ptr, 50, stdin) != NULL) {
// Counting ‘x’ Characters
  while(*ptr != '\0') {
    if (*ptr == 'x') {
      xcount++;
    }
    ptr++;
  }
}
free(ptr);
```

**Problem**

- **Pointer Increment**: The **`ptr`** pointer is incremented in the loop, so by the time **`free(ptr)`** is called, **`ptr`** no longer points to the original memory block allocated by **`malloc`**.
- **Undefined Behavior**: Freeing a pointer that was not returned by **`malloc`** (or related functions like **`calloc`** or **`realloc`**) results in undefined behavior, which can cause the program to crash or exhibit other unexpected behavior.

**Solution**

To fix this issue, you should use a separate pointer to iterate through the string, while keeping the original pointer for freeing the memory:

```c
int xcount = 0;
char * ptr = malloc(50 * sizeof(char));
char * original_ptr = ptr; // Keep the original pointer
if (fgets(ptr, 50, stdin) != NULL) {
  while(*ptr != '\0') {
    if (*ptr == 'x') {
      xcount++;
    }
    ptr++;
  }
}
free(original_ptr); // Free the original pointer
```

## malloc、realloc

**`realloc`** 分配的内存地址是否与之前 **`malloc`** 分配的内存地址一致，主要由程序自动管理，程序员无法直接控制 **`realloc`** 是否会返回相同的内存地址。

Whether the memory address allocated by **`realloc`** is the same as the one previously allocated by **`malloc`** is mainly managed automatically by the program. Programmers cannot directly control whether **`realloc`** will return the same memory address.

both **`p`** and **`m`** could be passed as the first argument to a call to **`realloc`**. 

```c
int * p = malloc(12*sizeof(*p));
char * q = malloc(14*sizeof(*q));
char * m = q;
q++;
int ** ptr= &p;
```

Here’s a breakdown:

1. **`p`**: This is a pointer to an array of integers allocated by **`malloc`**. You can pass **`p`** to **`realloc`** to resize this array.
2. **`m`**: This is a pointer to the same memory location as **`q`** before **`q`** was incremented. Since **`m`** points to the start of the memory block allocated by **`malloc`**, it can also be passed to **`realloc`**.

However, **`q`** should not be passed to **`realloc`** because it has been incremented and no longer points to the start of the allocated memory block.

Here’s an example of how you might use **`realloc`** with **`p`** and **`m`**:

```c
p = realloc(p, 24 * sizeof(*p)); // Resize the integer array pointed to by p
m = realloc(m, 28 * sizeof(*m)); // Resize the character array pointed to by m
```

# Module 3

## Abstraction

analogies for each of the options in the context of programming:

1. **Word**: A **single line of code** or a **variable**. Just as a word is the smallest unit of meaning in a sentence, a single line of code or a variable is a basic unit in a program.
2. **Sentence**: A single **statement** or **command** in a program. Just as a sentence conveys a complete thought, a statement or command performs a specific action in the code.
3. **Paragraph**: A **function** or a **method**. Just as a paragraph contains a series of sentences that together convey a complete idea, a function contains a series of statements that together perform a specific task.
4. **Chapter**: A **module** or a **class**. Just as a chapter is a section of a book that covers a particular topic, a module or class is a section of a program that encapsulates related functions and data.
5. **Book**: The **entire program or software application**. Just as a book is a complete work composed of chapters, a program is a complete application composed of modules and functions.

These analogies help illustrate how different components of a program relate to elements of writing.

# Module 4
## Monte Carlo simulation
