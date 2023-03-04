/*
*Description:
This file will holde all of the code relating to daemons.
*Created:
01/03/2023
*Last Modified:
04/03/2023
*Author:
Paul Geoghegan
*/

#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <unistd.h>

	static void daemonMaker() {

	//Creates child process to become daemon
	int pid = fork();

	//Checks for parent and child
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	}
	else if(pid == 0) {

		if(setsid() < 0) {
			exit(EXIT_FAILURE);
		}
		else {

			//reset signals for daemon
			signal(SIGCHLD,SIG_IGN);
			signal(SIGHUP, SIG_IGN);

			//Forks again to ensure daemon can't be attached toa terminal as only the session leader can do this
			pid = fork();

			if(pid > 0) {
				exit(EXIT_SUCCESS);
			}
			else if(pid == 0) {

				//Changes to route directory to avoid problems with mounted drives
				chdir("/");

				//Changes file permitions
				umask(0);

				//Closes all file descriptors
				for(int x = 0;x <= sysconf(_SC_OPEN_MAX);x++) {
					close(x);
				}

				//Opens log file
				openlog("reportManagerDaemon",LOG_PID,LOG_DAEMON);
			}
			else {
				exit(EXIT_FAILURE);
			}
		}
	}
	else {
		exit(EXIT_FAILURE);
	}
}
