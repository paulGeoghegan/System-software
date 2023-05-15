/*
*Description
This function will control the server
*Author
Paul Geoghegan
*/

#include <arpa/inet.h>
#include "server.h"

#define maxClients 20

void fileSaver(int);

int main() {
	printf("Starting Server!\n");
	//Sets up variables
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addrSize;
	pid_t pid;

	//Sets up server socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	//Checks for errors
	if(serverSocket<0) {
		printf("Failed to create socket\n");
		return -1;
	}
	printf("The socket was created successfully\n");

	//Sets socket details
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2001);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Tries to bind to port
	if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0) {
		printf("Sorry couldn't bind the socket\n");
		return -1;
	}
	printf("The socket has been successfully bound\n");

	//Listen for a max of 4connections
	if(listen(serverSocket,maxClients)<0) {
		printf("Sorry couldn't listen for client connections\n");
		return -1;
	}
	printf("Listening for clients\n");

	//Loops forever
	while(1) {
		addrSize = sizeof(serverStorage);
		//Connects to first client in the que
		clientSocket = accept(serverSocket, (struct sockaddr*) &serverStorage, &addrSize);
		//Checks if connection was a success
		if(clientSocket < 0) {
			printf("Couldn't connect to client\n");
			return -1;
		}
		else {
			//Creates child process
			pid = fork();
			if(pid==0) {
				fileSaver(clientSocket);
				//Closes client
				close(clientSocket);
				//Makes process exit
				exit(0);
			}
			else if(pid<0) {
				printf("Couldn't create process");
				break;
			}
		}
	}

	//Closes socket
	close(serverSocket);
	printf("Socket Closed\n");

	return 0;
}

