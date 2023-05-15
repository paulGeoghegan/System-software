/*
*Description
This function will control the server
*Author
Paul Geoghegan
*/

#include <arpa/inet.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#define maxPthreads 4

//Global variables
sem_t x,y;
int currentPthreads=0;

//Function Declarations
void fileSaver(void*);

int main() {
	printf("Starting Server!\n");
	//Sets up variables
	int serverSocket, clientSocket;
	struct sockaddr_in serverAddr, clientAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addrSize;
	sem_init(&x,0,1);
	sem_init(&y,0,1);
	pthread_t pthreadId[maxPthreads];
	int i = 0;

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
	if(listen(serverSocket,maxPthreads)<0) {
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
			//Saves id to be passed as pointer
			idPointers[i]=clientSocket;
			//Creates thread for saving file
			if(pthread_create(&pthreadId[i++],NULL,fileSaver,(void*)(id[i-1]))<0) {
				printf("Error Creating thread\n");
			}

		}
	}

	//Closes socket
	close(serverSocket);
	printf("Socket Closed\n");

	return 0;
}


void fileSaver(void* clientSocket) {

	char serverMessage[100],clientMessage[100];

	//Locks semaphore to increase count
	sem_wait(&x);
	currentPthreads++;
	if(currentPthreads==1) {
		sem_wait(&y);
	}
	sem_post(&x);
	printf("There are %d threads reading",currentPthreads);
	sleep(5);

	//Gets client message
	if(recv(*clientSocket,&clientMessage,sizeof(clientMessage),0)<0) {
		printf("Error receiving data from client\n");
		strcpy(serverMessage,"failed");
	}
	else {
		printf("Client data: %s\n",clientMessage);
		strcpy(serverMessage,"success");
	}

	//Sends server message
	if(send(*clientSocket,serverMessage,strlen(serverMessage),0)<0) {
		printf("Failed to report %s to socket\n",serverMessage);
	}
	else {
		printf("Reported %s to socket\n",serverMessage);
	}

	//Locks semaphore to decrease count
	sem_wait(&x);
	currentPthreads--;
	if(currentPthreads==0) {
		sem_post(&y);
	}
	sem_post(&x);
	printf("%d threads finishing",currentPthreads+1);
	pthread_exit(NULL);
}