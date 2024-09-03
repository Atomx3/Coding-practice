# Duke- C1w3- Overflow

Date: December 13, 2023

[https://www.coursera.org/learn/programming-fundamentals/](https://www.coursera.org/learn/programming-fundamentals/home/welcome)

[How to calculate binary, decimal, hexadecimal](https://www.rapidtables.com/convert/number/hex-to-decimal.html)

**3 parts of fields compound a float number.**

the most significant bit (MSB) 最高有效位

exponent 指数

mantissa 尾数

IEEE floating point Standard

**unsigned integer** 无符号整数 that can only hold zero and positive numbers. For an n-bit integer, the range of values it can represent is[ 0 , 2^n ].

**signed integer**, For an n-bit integer, the range of values it can represent is[ -2^(n-1) , 2^(n-1) - 1].

convert the signed 2’s complement decimal number to its binary representation step by step:

**eg.**

the signed 2’s complement decimal number 

signed int n= `-3` 
• The absolute value `3`, binary `0011`

invert bits as `1100`.

add 1 to the last bit.  `1101`.

the signed 2’s complement binary representation in 32 bits as.

`11111111111111111111111111111101`

[Decimal to Binary Converter (rapidtables.com)](https://www.rapidtables.com/convert/number/decimal-to-binary.html)

implicit conversion/ `(float)`explicit cast

隐式转换/ `(float)`显式强制转换

```c
int main(void) {
int nHrs = 40;
int nDays = 7;
float avg = nHrs/(float)nDays;

40/7.0 ➡️ 40.0/7.0

nDays = 7 by explicit cast, changed to avg = 40/7.0 firstly;
nHrs = 40 by implicit conversion, changed to 40.0 then;
avg = 40.0/7.0 start calculation and get right result at last;
```

**Overflow and Underflow 上溢和下溢**

xkcd comic [http://xkcd.com/571/](http://xkcd.com/571/)

counting sheep comic, left and right game.

**calculate process and method:**

set 1 byte for an example.

|  | **decimal**  | **binary** | **transformation** |
| --- | --- | --- | --- |
| positive | 0 | 00000000 |  |
| head 0 in binary | 127 | 01111111 |  |
| negative  | 128 | 10000000 | -128 |
|  | 129 | 10000001 | -127 |
|  | 154 | 11111110 | -2 |
| head 1 in binary | 255 | 11111111 | -1 |

for the signed integers, that can only negative, zero and positive numbers. so divide a half number for the positions of negative integers.

[11111111, 00000000]

[-128,-1]  [0,127] 

[10000000, 11111111] [00000000, 01111111]

if there is a variable value 128, then PC will return a value as -128

variable value 129, return value as 0

run the code and change the input value, to test the output result(in error report).

```c
#include <stdio.h>
int main() {
signed char x = 128;
printf("%d\n", x);
return 0;
}

the program will report erro, it shows :
implicit conversion from 'int' to 'signed char' changes value 
from 128 to -128 
from 129 to -127
……
[-Werror,-Wconstant-conversion]
```

### Consider the following operation that overflows:

```c
char c = 250;
c += 8;
```

What value does c have after the above statements are executed? (Give your answer as a decimal integer.)

answer: 2 ?

please write down the calculate steps

```c
// **take the above [decimal 	binary	transformation] table for reference.

signed char is 8 bit totally, it is seperated to two parts.**
positive int[0,127]
negative int[-128,-1] //implicit conversion from positive int[128,255]

258 - 255= 3

overflow sequences 255, 256 that map separately to integer -1, 0. 

**count from 0, so 3-1 left 2?**
```

| decimal value | overflow value  |
| --- | --- |
| 255 | -1 |
| 256 | 0 |
| 257 | 1 |
| 258 | 2 |

what’s meaning of **Printing redux?**

# [enumerated types](https://www.coursera.org/learn/programming-fundamentals/supplement/a7zEW/enumerated-types)

`enum`

# Struct ?

`Struct`, A programming construct that bundles variables into a logical group. 

`typedef`, Make alias for an existing type name, it is not only used with struct.

[C typedef (w3schools.in)](https://www.w3schools.in/c-programming/typedef)

```c
struct point_tag {
  double x;
  double y;
};
typedef struct point_tag point_t;
```

the correctly declare struct are:

```c
point_t myPoint;
struct point_tag myPoint;
```

~~wrong declare a struct are:~~

```c
point_tag myPoint;
struct point_t myPoint;
```

why?

# Largest value

What is the largest value that can be represented by a 32-bit int, expressed in hex? (Be sure to prepend your answer with "0x", and write any letters as capitals)

**for Signed integers**

| **bit** | **binary** | **decimal** | **hexadecimal** |
| --- | --- | --- | --- |
| 32 | 01111111 11111111 11111111 11111111  | 2147483647 | 7FFFFFFF/ 0x7FFFFFFF |
| 16 | 01111111 11111111  | 32767 | 7FFF/ 0x7FFF |
| 8 | 01111111 | 127 | 7F/ 0x7F |
| 4 | 0111 | 7 | 7/ 0x7 |

**for Unsigned integers**

| **bit** | **binary** | **decimal** | **hexadecimal** |
| --- | --- | --- | --- |
| 32 | 11111111 11111111 11111111 11111111  | 4294967295 | FFFFFFFF/ 0xFFFFFFFF |
| 16 | 11111111 11111111  | 65535 | FFFF/ 0xFFFF |
| 8 | 11111111 | 255 | FF/ 0xFF |
| 4 | 1111 | 15 | F/ 0xF |

a short integer is 16 bits, what is the largest integer of it?

normally it is assumed as signed, so it can represent values from **-32768 to 32767.** 

where n is the number of bits, the maximum value is

$2^(n−1) −1$ for signed

$2^n−1$ for unsigned

The output of the value is 4.67 (rounding)

```c
double d = 4.669;
printf("My number is %.2f.",d);
```

# **Writing a Sorting Algorithm**

data source [https://www.ncdc.noaa.gov/sotc/global-regions/201701](https://www.ncdc.noaa.gov/sotc/global-regions/201701)

| **Continent** | **Anomaly (C)** |
| --- | --- |
| North America | 3.18 |
| South America | 1.36 |
| Europe | -0.12 |
| Africa | 0.53 |
| Asia | 1.92 |
| Oceania | 0.98 |

Step 1. **Work an example by hand**

Step 2. **Write down exactly what you did**

1 select 0 as a first compare number, 

is there a number equal to 0 on the first position before decimal point?

yes, then input 0 in the middle of table sheet;

2 if there are numbers less than 0?

2.1. no, all are positive numbers.

2.1.1.  let’s count from 0 after the decimal point.

what's the number on the first position after decimal point?

is there a 0 on the first position? no, let’s count 1, 2, 3, …… 9 .

5 is the smallest, so input this number 0.53 as the smallest number on the list.

then 9, input 0.98 on the second position of the list.

2.1.2. let's count from 1 before the decimal point. (we have sorted 0 already)

how many digit of the number before the decimal point? what’s the smallest number? 

only 1 digit before decimal point. 

from 0 to 9, what’s the smallest number of this 1 digit number? 

1 is the smallest, then count what’s the smallest after the decimal point part.

3 is less than 9,

so 1.36 is listed on the sorting table.

then 1.92 is listed.

continue counting, the number greater than 1 

3 is next one, so 3.18 is listed

we have counted all numbers already.

end.

2.2. yes, there are numbers less than 0, pick them out, and continue compare.

if there are numbers that larger than 0 before decimal point?

yes, let's count how many digit of the number before decimal point?

…… 

the same process as the 2.1 part above.