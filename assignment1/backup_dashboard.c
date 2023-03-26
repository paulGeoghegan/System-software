#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>


void backup_dashboard(void) {

    syslog(LOG_INFO,"Backing up reports");

	char names[4][14] = {"warehouse","manufacturing","•	sales","distribution"};
    char source[] = "/home/paul/System-software/assignment1/reporting/";
    char destination[] = "/home/paul/System-software/assignment1/backup/";
	struct dirent *dir;
	DIR *dr = opendir("/home/paul/System-software/assignment1/uploads");

	if(dr == NULL) {
		syslog(LOG_ERR,"The uploads folder does not exist");
	}
	else {
		while ((dir = readdir(dr)) != NULL) {
			for(int i = 0;i < 4;i++) {
                int success = rename(strcat(source,names[i]),strcat(destination,names[i]));
                if(success== -1) {
                    syslog(LOG_ERR,"The %s file could not be moved to the reporting directory",names[i]);
                }
			}
		}
		closedir(dr);
	}
}
