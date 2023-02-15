#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main( int argc, char *argv[]) {
	//Creates child process
	pid_t pid = fork();

	if(argc == 1) {
		//Only runs if child process exicutes it
		if(pid == 0) {
			//Creates pointer array to be passed to execv as it needs a program to run which will be /bin/ls which will exicute the ls command and then -al which will be the peramiter passed to it
			char *commandList[] = {"/bin/ls", "-al", NULL};
		//Here we pass the /bin/ls file as arg1 and then the adress to the pointer array using the & opporator as arg2
			execv(commandList[0], &commandList[0]);
		}
	}
	else if(argc > 1) {
		//Sets up kill command
		char *commandList[] = {"/bin/kill",argv[1],NULL};

		if(pid == 0) {
			execv(commandList[0],&commandList[0]);
		}
	}
	else {
		return 1;
	}
	return 0;
}