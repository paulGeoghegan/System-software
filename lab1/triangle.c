#include <stdio.h>

int triangle(int s1, char s2) {
	int side1 = s1;
	int side2 = s2;
	printf("Side1 = %d", side1);
	printf("Side2 = %d", side2);
	int area = (side1*side2)/2;
	printf("Area of triangle = %d", area);
}