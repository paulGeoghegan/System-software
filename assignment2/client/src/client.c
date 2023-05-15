/*
*Description
This function will control the client
*Author
Paul Geoghegan
*/

#include <arpa/inet.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	printf("Starting client and connecting to server\n");
	int clientSocket;
	struct sockaddr_in serverAddr;
	uid_t userId;
	//Max filepath in linux is 4096 bytes so we use this as the length of the path plus 1 for \0
	char serverMessage[256],clientMessage[4097],filePath[4097],fileData[1024];
	FILE *clientFile;

	//Creates client socket
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);

	//Checks if socket was created
	if(clientSocket<0) {
		printf("Couldn't create client\n");
		close(clientSocket);
		return -1;
	}

	//Sets socket details for the server to connect to
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2001);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Tries to connect
	if(connect(clientSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr))<0) {
		printf("Couldn't connect to server\n");
		close(clientSocket);
		return -1;
	}
	printf("Connection established\n");

	//Gets user data
	userId = getuid();

	//Tries to send data
	if(send(clientSocket,&userId,sizeof(userId),0)<0) {
		printf("Couldn't send data\n");
		close(clientSocket);
		return -1;
	}
	printf("User info sent to server\n");

	//Gets response
	if(recv(clientSocket,&serverMessage,sizeof(serverMessage),0)<0) {
		printf("Couldn't get message from server\n");
		close(clientSocket);
		return -1;
	}
	printf("Server said: %s\n",serverMessage);

	//Gets file path
	printf("Please enter the file path for the file you wish to upload:\n");
	scanf("%4096[^\n]%*c", filePath);
	printf("You entered %s\n",filePath);

	//Opens file
	clientFile = fopen(filePath,"r");
	if(clientFile == NULL) {
		printf("Sorry that file couldn't be opened\n");
		close(clientSocket);
		return -1;
	}

	//Reads and sends file
	while(fgets(fileData,1024,clientFile)!=NULL) {
		printf("%s",fileData);
		if(send(clientSocket,fileData,sizeof(fileData),0)<0) {
			printf("Couldn't send bytes from file");
			close(clientSocket);
			return -1;
		}
		bzero(fileData,1024);
	}

	//Gets response
	if(recv(clientSocket,&serverMessage,sizeof(serverMessage),0)<0) {
		printf("Couldn't get message from server\n");
		close(clientSocket);
		return -1;
	}
	printf("Server said: %s\n",serverMessage);

	//Closes socket
	close(clientSocket);

	return 0;
}