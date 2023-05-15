/*
*Description
This function will be ran by each thread in order to save the files from the user
*Author
Paul Geoghegan
*/

#include <grp.h>
#include <pwd.h>
#include <time.h>

void fileSaver(int clientSocket) {

	uid_t userId;
	struct passwd *user;
	struct group *usersGroup;
	struct tm *timeStruct;
	char serverMessage[256],clientMessage[4097],timeString[30];
	FILE *clientFile;
	char filePath[4097]="/home/paul/System-software/assignment2/server/reports/";
	char clientData[1024];
	time_t currentTime = time(NULL);
	timeStruct=gmtime(&currentTime);
	int n;

	//Gets client message
	if(recv(clientSocket,&userId,sizeof(clientMessage),0)<0) {
		printf("Error receiving data from client\n");
		return;
	}
	else {
		//Users id to get userinfo
		user = getpwuid(userId);
		printf("Client name: %s\n",user->pw_name);
		strcpy(serverMessage,"found user ");
		strcat(serverMessage,user->pw_name);
	}

	//Sends server message about user validation
	if(send(clientSocket,serverMessage,strlen(serverMessage),0)<0) {
		printf("Failed to report %s to socket\n",serverMessage);
		return;
	}

	//Gets groupnames
	usersGroup = getgrgid(user->pw_gid);
	//Checks if user is in either group and creates file path
	if(strcmp("distribution",usersGroup->gr_name)==0||strcmp("manufacturing",usersGroup->gr_name)==0) {
		strcat(filePath,usersGroup->gr_name);
		strcat(filePath,"/");
		strcat(filePath,user->pw_name);
		strcat(filePath,"-");
		strftime(timeString,sizeof(timeString),"_%Y-%m-%d_%H:%M:%S",timeStruct);
		strcat(filePath,timeString);
		strcat(filePath,".txt");
		printf("%s",filePath);
		clientFile = fopen(filePath,"w");
		//Loops and writes to file
		while(1) {
			n = recv(clientSocket,&clientData,sizeof(clientData),0);
			if(n<=0) {
				break;
			}
			fprintf(clientFile,"%s",clientData);
			bzero(clientData,1024);
		}
		//Closes file
		fclose(clientFile);
		//Changes ownership
		if((chown(filePath,user->pw_uid,user->pw_gid))!=0) {
			printf("Can't change ownership");
			strcpy(serverMessage,"File saved but ownership wasnt changed");
			if(send(clientSocket,serverMessage,strlen(serverMessage),0)<0) {
				printf("Failed to report non ownership change to client");
			}
			return;
		}
		printf("File saved and ownership was set");
		strcpy(serverMessage,"Your file was saved and ownership has been set");
		if(send(clientSocket,serverMessage,strlen(serverMessage),0)<0) {
			printf("Failed to report success to client");
		}
	}
	else {
		printf("No group with access found");
		strcpy(serverMessage,"you are not a member of any groups with access to upload files");
		if(send(clientSocket,serverMessage,strlen(serverMessage),0)<0) {
			printf("Failed to report invalid group to client");
		}
		return;
	}

}