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
