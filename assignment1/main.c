/*
*Description:
This is the main file for my assignment it will mainly handle calling other functions.
*Created:
01/03/2023
*Last Modified:
04/03/2023
*Author:
Paul Geoghegan
*/

#include "daemonUtils.h"
#include <syslog.h>
#include <unistd.h>


int main() {

	//Creates damon
	daemonMaker();

	while(1) {
		syslog(LOG_NOTICE,"Daemon for report management has been created");
		sleep(10);
		break;
	}


	syslog(LOG_NOTICE,"Daemon now terminated");
	closelog();
	return EXIT_SUCCESS;
}