
# C-Duke Course 4 Interacting with the System and Managing Memory Module 1 


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
