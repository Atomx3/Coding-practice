# Duke- C1w2- Reading code

Date: November 15, 2023

**Quiz**

Execute the following code by hand:

```c
int anotherFunction(int a, int b) {
  int answer = 2;
  int x = 0;
  printf("In anotherFunction(%d,%d)\n",a,b);
  while (b > a) {
    printf("a is %d, b is %d\n", a, b);
    answer = answer + (b - a);
    b -= x;
    a += x / 2;
    x++;
  }
  return answer;
}

int someFunction(int x, int y) {
  int a = x + y;
  if (x < y) {
    for (int i = 0; i < x; i++) {
      printf("In the loop with i = %d, a = %d\n", i, a);
      a = a + x;
    }
  }
  else {
    y = anotherFunction(y,a+1);
  }
  return a * (y-10);
}

int main(void) {
  int x = 2;
  int b = someFunction(3,x);
  printf("b = %d\n", b);
  printf("x = %d\n", x);
  return 0;
}
```

Execute main

```c
main

//setep 1, execute main box, jump to calculate functions in b box.

// get result from step 3 in y box, print first 4 lines
In anotherFunction(2,6) 
a is 2, b is 6
a is 2, b is 6
a is 2, b is 5

//step 5, come back to main box, input last step value b=15
//step 6, print last two lines.
b=15;
x=2;
```

b = someFunction(3,2);

```c
**b** 

x=3
y=2 
a=5
y = anotherFunction(y,a+1)

//setep 2, execute b box
//step 4, come back to b box, input value y=13
// because in or after else condition expression, there is no loop, just 
go to the last one return a * (y-10) = 15

```

y = anotherFunction(2,6)

```c
y
//setep 3, execute y box
// execute loops and print the first 4 lines in main box as below

In anotherFunction(2,6)
a is 2, b is 6
a is 2, b is 6
a is 2, b is 5

// continue loops and until the 4th time, while b > a is false, 
// end the loop, return the first value 13
! hint: when calculate int a= x/2, if x=5, then a = 2(not 3); 
```

| y  | 1st | 2nd | 3rd | 4th | end |
| --- | --- | --- | --- | --- | --- |
| a= | 2 | 2 | 2 | 3 |  |
| b= | 6 | 6 | 5 | 3 |  |
| x= | 0 | 1 | 2 | 3 |  |
| answer= | 2 | 6 | 10 | 13 | return answer=13 |