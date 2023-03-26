#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <syslog.h>
#include <stdio.h>
#include <stdlib.h>


void unlock_directories() {

    int pid = fork();
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    } else {
        //Sets up args list
        char *args[] = {"/bin/chmod", "0777", "/home/paul/System-software/uploads", "/home/paul/System-software/reporting", NULL};
        //Exicutes command
execv(args[0],args);
       }
}