#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rectangle.h"
#include "triangle.h"
#include "circle.h"

int main(int argc, char **argv) {
	if(!strcmp(argv[1], "rectangle")) {
		rectangle(atoi(argv[2]), atoi(argv[3]));
	}
	else if(!strcmp(argv[1], "triangle")) {
		triangle(atoi(argv[2]), atoi(argv[3]));
	}
	else if(!strcmp(argv[1], "circle")) {
		circle(atoi(argv[2]));
	}
	else {
		printf("Sorry you're input wasn't valid");
	}
	return 0;
}