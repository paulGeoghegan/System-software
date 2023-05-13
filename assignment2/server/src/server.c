/*
*Description
This function will control the server
*Author
Paul Geoghegan
*/

#include <arpa/inet.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

//Global variables
sem_t x,y;
pthread_t fileReaderThreads[4];
int currentFileReaderThreads=0;

//Function Declarations
void* fileReader(void*);

int main() {
	printf("Starting Server!\n");
	//Sets up variables
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addrSize;
	sem_init(&x,0,1);
	sem_init(&y,0,1);
pthread_t threadId[4];
	int i = 0;
	char serverMessage[100],clientMessage[100];

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
	serverAddr.sin_port = htons(2000);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	//Tries to bind to port
	if(bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr))<0) {
		printf("Sorry couldn't bind the socket\n");
		return -1;
	}
	printf("The socket has been successfully bound\n");

	//Listen for a max of 4connections
	if(listen(serverSocket,4)<0) {
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
			//Gets client message
			if(recv(clientSocket,&clientMessage,sizeof(clientMessage),0)<0) {
				printf("Error receiving data from client\n");
				strcpy(serverMessage,"failed");
			}
			else {
				printf("Client data: %s\n",clientMessage);
				strcpy(serverMessage,"success");
			}

			//Sends server message
			if(send(clientSocket,serverMessage,strlen(serverMessage),0)<0) {
				printf("Failed to respond to client\n");
				return -1;
			}
			printf("Reported %s to socket",serverMessage);
		}
	}

	//Closes socket
	close(serverSocket);
	printf("Socket Closed\n");

	return 0;
}

void* fileReader(void*) {
	//Locks semaphore to increase count
	sem_wait(&x);
	currentFileReaderThreads++;
	if(currentFileReaderThreads==1) {
		sem_wait(&y);
	}
	sem_post(&x);
	printf("There are %d threads reading",currentFileReaderThreads);
	sleep(5);
	//Locks semaphore to decrease count
	sem_wait(&x);
	currentFileReaderThreads--;
	if(currentFileReaderThreads==0) {
		sem_post(&y);
	}
	sem_post(&x);
	printf("%d threads finishing",currentFileReaderThreads+1);
	pthread_exit(NULL);
}