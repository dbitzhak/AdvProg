#include "Server.h"
#include "CommandsManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <utility>
#include <pthread.h>
#include <cstdlib>

typedef void * (*funcPointer)(void *);

#define MAX_CONNECTED_CLIENTS 10

struct ThreadArgs {
 int clientSocket;
 CommandsManager *commandsManager;
};



Server::Server(int port, CommandsManager *cm): port(port), serverSocket(0) , serverOn(false), commandsManager(cm){
 cout << "Server" << endl;
}
void Server::start() {
	serverOn = true;
	// Create a socket point
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1) {
		throw "Error opening socket";
	}
	// Assign a local address to the socket
	struct sockaddr_in serverAddress; //Internet socket address
	bzero((void *)&serverAddress, sizeof(serverAddress)); //Fills with zeroes
	serverAddress.sin_family = AF_INET; //Generally used type
	serverAddress.sin_addr.s_addr = INADDR_ANY; //Sets server address
	//Converts the unsigned short integer hostshort f/ host byte order to network byte order.
	serverAddress.sin_port = htons(port);
	//If binding fails throws exception
	if (::bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		throw "Error on binding";
	}
	//Create a thread for closng the server
	pthread_t threadStop;
	runningThreads.push_back(threadStop); //Add for thread control
	int result = pthread_create(&runningThreads.back(), NULL,(funcPointer) &Server::stop, this); //Run acceptClients
	if (result) {
		cout << "Error: unable to create thread, " << result << endl;
		exit(-1);
	}
	//Create a thread for listening to client connections
	pthread_t newThread;
	runningThreads.push_back(newThread); //Add for thread control
	result = pthread_create(&runningThreads.back(), NULL,(funcPointer) &Server::acceptClients, this); //Run acceptClients
	if (result) {
		cout << "Error: unable to create thread, " << result << endl;
		exit(-1);
	}
}



pair<int,int> Server::receiveMove(int socket) {
	int x, y;
	
	// Read new move argument from client
	long n = read(socket, &x, sizeof(x));
	if (n == -1) {
		throw "Error reading x";
	}
	if (n == 0) {
		throw "Client disconnected";
	}
	n = read(socket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading y";
	}
	
	cout << "Got move from client: " << x << ", " << y << endl;

	return make_pair(x, y);

}

void Server::passMove(pair<int,int> move, int socket) {
	long n;
	try {
		n = write(socket, &move.first, sizeof(move.first));

	} catch(exception e) {
		cout << "passMove: Error writing x to socket" << endl;
		throw "Error writing x to socket\n";
	}
	if (n == -1) {
		cout << "passMove: Error writing x to socket" << endl;
		throw "Error writing x to socket\n";
//		return;
	}
	try {
		n = write(socket, &move.second, sizeof(move.second));
	} catch(exception e) {
		cout << "passMove: Error writing y to socket" << endl;
		throw "Error writing y to socket\n";
//		return;
	}
	if (n == -1) {
		cout << "passMove: Error writing y to socket" << endl;
		throw "Error writing y to socket\n";
//		return;
	}
}

void Server::alertClient(int socket) {
	try {
		passMove(pair<int,int>(ERROR,ERROR), socket);
	} catch (const char *msg) {
		cout << msg;
	}
}

// Handle requests from a specific client
void * Server::handleClient(void * args) {
	ThreadArgs *ta = (struct ThreadArgs*) args;
	ThreadArgs temp;
	temp.clientSocket = ta->clientSocket;
	temp.commandsManager = ta->commandsManager;
	delete ta; //Frees the memory
	return temp.commandsManager->getUserCommand(temp.clientSocket);
}


void Server::stop() {
	serverOn = false;
	close(serverSocket);
}

void * Server::acceptClients() {
	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);
	while (serverOn) {
		cout << endl << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "New client connected" << endl;
		if (clientSocket == -1) {
			throw "Error on accept";
		}
		cout << "Waiting for other clients..." << endl;

		//Creates a new thread to handle client's request
		ThreadArgs * args = new ThreadArgs();
		args->clientSocket = clientSocket;
		args->commandsManager = this->commandsManager;
		pthread_t newThread;
		runningThreads.push_back(newThread); //Add for thread control
		int result = pthread_create(&runningThreads.back(), NULL, Server::handleClient,(void *) args); //Run handleClient
		if (result) {
		 cout << "Error: unable to create thread, " << result << endl;
		 exit(-1);
		}
	}
	return 0;
}
