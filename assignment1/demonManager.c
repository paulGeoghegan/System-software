/*
*Description:
This file will holde all of the code relating to demons.
*Created:
01/03/2023
*Last Modified:
01/03/2023
*Author:
Paul Geoghegan
*/

#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>


static void demonMaker() {

	//Creates child process to become demon
	int pid = fork();

	//Checks for parent and child
	if(pid > 0) {
		sleep(3);
		print("Detaching demon");
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0) {

		

		//Makes sure the demon exits
		return 0;
	}

}