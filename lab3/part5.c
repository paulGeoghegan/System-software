#include <unistd.h>
#include  <stdio.h>
#include <sys/types.h>


int main() {
	char name[30];
	pid_t pid = fork();
	if(pid == 0) {
		//Creates file
		FILE *logFile = fopen("logFile.txt","a+");
		if(logFile == NULL) {
			printf("Couldn't open log file");
			fclose(logFile);
			return 1;
		}
		else{
			printf("File created What is your name:");
			fgets(name,30,stdin);
			fprintf(logFile,"%s",name);
			fclose(logFile);
		}
	}
	return 0;
}