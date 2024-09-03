# Duke- C2w2- Rectangle

Date: November 26, 2023

[Assignment 06_rect](https://www.coursera.org/learn/writing-running-fixing-code/programming/uxVzJ/assignment-06-rect)

reference:

[struct and typedef for rectangles](https://www.coursera.org/learn/programming-fundamentals/supplement/9LmqH/structs) 

[Intersection of Two Rectangles](https://www.coursera.org/learn/writing-running-fixing-code/lecture/Izza8/intersection-of-two-rectangles)

[Completed Rectangle Intersection Code](https://www.coursera.org/learn/writing-running-fixing-code/supplement/vBFSX/completed-rectangle-intersection-code)

```c
#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min (int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max (int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct rect {int x; int y; int width; int height;};
typedef struct  rect rectangle;

rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if (r.width < 0) {
       r.x = r.x + r.width;
       r.width = -r.width;
   }
   if (r.height < 0) {
       r.y = r.y + r.height;
       r.height = -r.height;
   }
  return r;
}

rectangle intersection(rectangle r1, rectangle r2) {
  //the input value r of function intersection, 
which is the output value from function canonicalize above, 
please correct the code.

  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  rectangle r;

   // Find the max of the x and y values for the intersection
   r.x = max(r1.x, r2.x);
   r.y = max(r1.y, r2.y);

   // Find the min of the x+width and y+height values for the intersection
   int r1_x_end = r1.x + r1.width;
   int r2_x_end = r2.x + r2.width;
   int r1_y_end = r1.y + r1.height;
   int r2_y_end = r2.y + r2.height;

   int r_x_end = min(r1_x_end, r2_x_end);
   int r_y_end = min(r1_y_end, r2_y_end);

   r.width = r_x_end - r.x;
   r.height = r_y_end - r.y;

   // If there is no intersection, set width and height to 0
   if (r.width < 0 || r.height < 0) {
       r.width = 0;
       r.height = 0;
   }
// Return the intersection rectangle
  return r;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y,
	                           r.x + r.width, r.y + r.height);
  }
}

int main (void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test intersection of r2, r3, r4 with r1
  rectangle i = intersection(r1,r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1,r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);

  i = intersection(r1,r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1,r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2,r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2,r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);

  i = intersection(r2,r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2,r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3,r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3,r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);

  i = intersection(r3,r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3,r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4,r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4,r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);

  i = intersection(r4,r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4,r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;

}
```

the hard point is how to transfer canonicalize value to intersection. 

**with the help of chatgpt, copilot**

comments keywords are  

```c
rectangle intersection(rectangle r1, rectangle r2) {
  //the input value r of function intersection, 
// which is the output value from function canonicalize above, 
// please correct the code.

```

# think about why such errors?

without the function below.

`r1 = canonicalize(r1);
 r2 = canonicalize(r2);`

the output value would be <empty> all as:

intersection(r1,r2): (2,3) to (7,9)

intersection(r1,r2): <empty>

intersection(r1,r3): <empty>

intersection(r1,r4): <empty>

if we change below `<` as `≤`

```c
if (r.width < 0 || r.height < 0) {
       r.width = 0;
       r.height = 0;
   }
```

intersection(r3,r4): <empty>

intersection(r3,r4): (-2,7) to (0,7), the overlapping shape is a line, the width is 2, but height is 0. we also print it out.

if we change above `||` as `&&` 

the wrong output will be as: 

intersection(r4,r1): (0,7) to (2,9)
intersection(r4,r2): (-1,5) to (0,7)

**no intersection, exclude below condition.** 

1. **r.width = 0 && r.height < 0**

r4 is (-4,7) to (0,9)

r5 is (0,3) to (2,6)

r.x= 0

r.y= 7

r.width = 0 - 0 = 0 

r.height = 6 - 7 = -1 

1. **r.width < 0 && r.height = 0**

r4 is (-4,7) to (0,9)

r5 is (1,4) to (5,7)

r.x= 1

r.y= 7

r.width= 0 - 1 = -1

r.height= 7 - 7 = 0 

**intersection is a line, include below condition.** 

1. **r.width > 0 &&  r.height = 0**

r3 is (-2,-3) to (5,7)

r4 is (-4,7) to (0,9)

r.x= -2

r.y= 7

r.width= 0 - (-2) = 2

r.height= 7- 7 = 0

intersection(r3,r4): (-2,7) to (0,7)

1. **r.width = 0 &&  r.height > 0**

r3 is (0,4) to (2,9)

r4 is (-4,7) to (0,9)

r.x= 0

r.y= 7

r.width= 0 - 0 = 0

r.height= 9- 7 = 2

intersection(r3,r4): (0,7) to (0,9)

## simplify above as mathematical symbols

**no intersection, exclude condition.** 

1. a **= 0 ∧ b < 0**
2. a **< 0 ∧ b = 0**

 = (a <0 ∨ b <0)

**intersection is a line, include condition.** 

1. a **> 0 ∧ b = 0**
2. a **= 0 ∧ b > 0**

= (a ≥0 ∨ b≥0)