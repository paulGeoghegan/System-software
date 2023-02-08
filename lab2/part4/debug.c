#include <stdio.h>
/*
This program will show how to use gdb to help debug a C program
1. run the gcc command with the -g flag so that it will be compiled for debugging:
gcc -g debug.c
2. run the gdb command with the output file from the previous command:
gdb a.out
3. Now we should set some break points to help us debug the problem
break 26
break 27
4. now we can run the program:
run
5. check the values of i and j to see what is going wrong
p i
p j
6. find the problem
in this case the problem is that the inner 4 loop doesn't run on the first time through the outer loop since i and j are both 0
we can fix this by changing the inner for to for(int j = 0;j <= i;j++)
*/

int main() {
	int rows;
	printf("How many rows do you want to print?\n");
	scanf("%d", &rows);
	//Prints rows
	for(int i = 0;i < rows;i++) {
		for(int j = 0;j < i;j++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}