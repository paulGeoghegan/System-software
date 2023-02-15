#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {

	FILE *logFile = fopen("logFile.txt","r");
	char line[30];

	if(logFile == NULL) {
		printf("Sorry that file doesn't exist");
		return 1;
	}
	else {
		while(fgets(line,30,logFile) != NULL) {
			printf("%s\n",line);
		}
	}
	fclose(logFile);
	return 0;
}