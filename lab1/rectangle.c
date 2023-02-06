#include <stdio.h>

int rectangle(int s1, char s2) {
	int side1 = s1;
	int side2 = s2;
	printf("Side1 = %d\n", side1);
	printf("Side2 = %d\n", side2);
	int area = side1*side2;
	printf("Area of rectangle = %d\n", area);
}