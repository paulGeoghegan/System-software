#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid = fork();
	//Only runs if child process exicutes it
	if(pid == 0) {
		//Creates pointer array to be passed to execv as it needs a program to run which will be /bin/ls which will exicute the ls command and then -al which will be the peramiter passed to it
		char *argv[] = {"/bin/ls", "-al", NULL};
	//Here we pass the /bin/ls file as arg1 and then the adress to the pointer array using the & opporator as arg2
		execv(argv[0], &argv[0]);
	}
	return 0;
}