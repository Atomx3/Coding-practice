# Duke- C2w2- Retirement

Date: November 30, 2023

**"retirement savings" calculator**

[Assignment 07_retirement](https://www.coursera.org/learn/writing-running-fixing-code/programming/HPpRY/assignment-07-retirement)

**Start** 

Age= 327 months (27 years, 3 months); Savings: `21,345`

**working**

489 months (40 years, 9 months); Savings: `1529340.57`

work until Age (68 years, 0 months(-1))

**retired**

384 months (32 years); Savings: `300234.07`

retired until Age(99 years, 11 months(-1), mark every month from 0 - 11 );

Died Age at (100 years, so only compute the 11th month, and don’t compute the last 12th month) 

```c
// "retirement savings" calculator
#include <stdlib.h>
#include <stdio.h>

// struct retirement information
struct _retire_info{int months; double contribution; double rate_of_return;};
typedef struct _retire_info retire_info;

//months, initial savings, info of working and retired.
void retirement (int startAge, double initial, retire_info working, retire_info retired)
  {double balance_current = initial;

   // compute and return a value list of years, months by the current age i;
   for (int i= startAge; i < startAge + working.months + retired.months; i++)
      {
       int year = i/12; // compute year, the mod of 12;
       int month = i%12; // compute month, the remainders of the year ;

      // first task, compute account balance each month while working.
     // At the start of each month (before the balance changes), print out the current balance
     if (i>startAge && i <= startAge+ working.months)
     {
       balance_current += balance_current* working.rate_of_return + working.contribution;
     }

     // Second task, compute account balance each month while retired
     // perform similar calculation as first task did,
     // abstract it's computation into a function and re-use it here,
     else if (i>startAge+ working.months)
     {
       balance_current += balance_current* retired.rate_of_return + retired.contribution;
     }

     printf("Age %3d month %2d you have $%.2lf\n", year, month, balance_current);

   }
   }

// pass arguments to function
int main(void) {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};
  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
  }
```

# Loop While

we can use `while` instead of `for`, but have to change the code order as below.

the **identifier '`i`'** must be declared before loop, `i++` could be in the same directory level of(before or after) `printf`.

```c
int i= startAge;
while (i < startAge + working.months)
{ if(){}
	else if(){}

i++;
printf();
}
```

be careful, `semi colon ;` is not allowed to used after or inside the  loop expression such as `(;);`  

## Do/ While

```c
int i= startAge;
{ if(){}
	else if(){}

i++;
printf();
}
while (i < startAge + working.months);
```

# Call function, pass arguments of an array

```c
int main(void) {
retire_info working = {489, 1000, 0.045 / 12};
retire_info retired = {384, -4000, 0.01 / 12};
retirement(327, 21345, working, retired);
}

// the another way to write code as below. 
{
		 retire_info working;
     retire_info retired;

     working.months= 489;
     working.contribution= 1000;
     working.rate_of_return= 0.045 / 12;

     retired.months= 384;
     retired.contribution= -4000;
     retired.rate_of_return= 0.01 / 12;
		 // call function retirement
		 retirement(327, 21345, working, retired);
}

// the above variables are initialized with the required values of array,
// then passed as arguments to the retirement function, 
// along with the startAge and initial values.
```

# Debugging

```c
if (i>startAge && i <= startAge+ working.months)
else if (i>startAge+ working.months)
```

correct output should be

> Age  27 month  3 you have $21345.00
Age  27 month  4 you have $22425.04
Age  67 month 11 you have $1522630.71
Age  68 month  0 you have $1529340.57
Age  68 month  1 you have $1526615.02
Age 99 month 11 you have $300234.07
> 

if we change operator `>,=, <`.

```c
if (i>=startAge && i < startAge+ working.months)
else if (i>=startAge+ working.months)

// if (i= startAge), it will start the computation since the startAge, 
// so we can not get the initial savings on the startAge/ no-change balance.
// instead a value that compute by the function
```

then wrong output will be 

> Age  27 month  3 you have $22425.04
Age  27 month  4 you have $23509.14
……
Age 99 month 11 you have $296484.27
> 

```c
if (i>startAge && i < startAge+ working.months)
else if (i>=startAge+ working.months)
// if (i< startAge+ working.months) 
// else if (i=startAge+ working.months)
// it will lost the last month computing while working, lost big money;
// then retired time was put forward one month ahead,
// so the balance changed smaller since the beginig of retired.
```

then wrong output will be 

> Age  68 month  0 you have $1519899.57
Age  68 month  1 you have $1517166.15
……
Age 99 month 11 you have $287245.16
> 

## Conditions if else

```c
if (condition1){}
else if (condition2){}
else {}
//this is correct, if we change it as below, then it will report errors
if (condition1){}
else (condition2){}
warning: else() expression result unused [-Wunused-value]

// if we delete (condition2), then the output value will be wrong as:
if (condition1){}
else {}
< Age  27 month  3 you have $17362.79
< Age  27 month  4 you have $18427.90
because the program jump over the condition1, and compute from else.
```