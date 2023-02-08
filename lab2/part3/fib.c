#include<stdio.h>    
void printFibonacci(int n){    
	//This initializes 3 static variables meaning that they will be kept in memory even if the function exits or runs again
    static int n1=0, n2=1, n3;    
	//This makes sure the user wants atleast 1 round of the sequence
    if(n>0){    
	//This sets n3 to 1+0 which is 1 but since the variables are static this changes every time the function is called since they are stored in memory
	//For example the second time the function runs n1 and n2 are both equal to 1 so it's 1+1 which is 2
         n3 = n1 + n2;    
		//This sets n1 to 1 and then 1 2 3 5 8 etc as the program progresses
         n1 = n2;    
		//This sets n2 to 1 and then 2 3 5 8 etc as the program progresses
         n2 = n3;    
         printf("%d ",n3);    
			//This calls the function again but decreases n by 1 to keep track of how many more times the program should run
         printFibonacci(n-1);    
    }    
} 
   
int main(){    
    int n;    
    printf("Enter the number of elements in the sequence: ");    
    scanf("%d",&n);    
    printf("Fibonacci Series: ");    
	//This prints the first 2 numbers in the sequence which is a problem since the user could enter 1 so they should only get the first number:0 but they will always get atleast 2 numbers even if they enter 0 or a negative number
    printf("%d %d ",0,1);    
	//This passes n to the print function with a -2 since we are already printing the first 2 numbers
    printFibonacci(n-2);    
  return 0;  
}    
