#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>

void check_file_uploads(void) {

	char names[4][14] = {"warehouse","manufacturing","•	sales","distribution"};
	struct stat info;
	struct dirent *dir;
	DIR *dr = opendir("/home/paul/System-software/assignment1/uploads");
	time_t t = time(NULL);
	struct tm currentTime = *localtime(t);
	char fileName[14];

	if(dr == NULL) {
		syslog(LOG_ERR,"The uploads folder does not exist");
	}
	else {
		FILE *reportsLog = fopen("/home/paul/System-software/assignment1/ReportLog.txt","w+");
		while ((dir = readdir(dr)) != NULL) {
			stat(dir->d_name,&info);
			strcpy(fileName,"NULL");
			for(int i = 0;i < 4;i++) {
				if(strstr(dir->d_name,names[i]) == NULL) {
					strcpy(fileName,names[i]);
				}
			}
			if(strcmp(fileName,"NULL")==0) {
				struct passwd *pws;
				pws = getpwuid(info.st_uid);
				fprintf(reportsLog,"%s: Last modified at: %d by: %s",dir->d_name,info.st_mtime,pws->pw_name);
			}
			else {
				fprintf(reportsLog,"The %s file was not uploaded on time",fileName);
			}
		}
		fclose(reportsLog);
		closedir(dr);
	}
}
      