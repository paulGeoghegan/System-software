/*
This program didn't work because it would decrease f from 5 like:
5 4 3 2 1 0
This meant that the last the time the function ran it would return 0
Since any number multiplied by 0 is 0 it would only ever return 0
There are 2 ways to fix this:
1. Change the return value to 1 instead of f inside of the if statement but this means it would run 1 aditional time
2. change if(f == 0) to if(f == 1) then it would return 1 instead of 0 fixing the problem
*/
#include <stdio.h>

long factorial(int);

int main()
{
   long f1;
   int f_num = 5;
   
   f1 = factorial(f_num);
   return 0;
}

long factorial(int f) {
   if(f == 1) {
      return f;
   } else {
      return f*factorial(f-1);
   }
}
