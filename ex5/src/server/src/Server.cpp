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
#include <sstream>

typedef void * (*funcPointer)(void *);

#define MAX_CONNECTED_CLIENTS 10
#define MAX_COMMAND_LEN 31
#define DISCONNECT -666

//Thread functions
static void *acceptClients(void *);
static void *handleClient(void *);
static void *endServer(void *);

///TODO TODO TODO - DELETE
static void *testFunction(long socket, CommandsManager *cm);
///TODO TODO TODO - DELETE


struct ThreadArgs {
	long serverSocket;
	long clientSocket;
	CommandsManager *commandManager;
};

Server::Server(int port, CommandsManager *cm): port(port), serverSocket(0) , serverOn(false), commandsManager(cm), serverThreadId(0) {
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
	if(::bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
			throw "Error on binding";
	}
	// Start listening to incoming connection requests
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	
	
	///TODO TODO TODO - DELETE
	testFunction(serverSocket, this->commandsManager);
	///TODO TODO TODO - DELETE
	
	
	//Create a thread for closing the server
	pthread_t threadStop;
	int result = pthread_create(&threadStop, NULL, &endServer, (void *) this); //Run stop
	if (result) {
		cout << "Error: unable to create thread, " << result << endl;
		exit(-1);
	}
	//Makes Server waits for threadStop
	pthread_join(threadStop, NULL);
	//Create a thread for listening to client connections
	ThreadArgs *args = new ThreadArgs;
	args->commandManager = commandsManager;
	args->serverSocket = serverSocket;
	result = pthread_create(&serverThreadId, NULL, &acceptClients,(void *) args); //Run acceptClients
	if (result) {
		cout << "Error: unable to create thread, " << result << endl;
		exit(-1);
	}
}


// Handle requests from a specific client
static void * handleClient(void * threadArgs) {
	ThreadArgs *ta =  (ThreadArgs*) threadArgs;	//Unpack thread args
	long clientSocket = ta->clientSocket;
	char commandStr[MAX_COMMAND_LEN];
	// Read the command from the socket
	long n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
	if (n == -1) {
		cout << "Error reading command" << endl;
		return NULL;
	}
	cout << "Received command: " << commandStr << endl;
	// Split the command string to the command name and the arguments
	string str(commandStr);
	istringstream iss(str);
	string command;
	iss >> command;
	vector<string> args;
	while (iss) {
		string arg;
		iss >> arg;
		args.push_back(arg);
	}
	ta->commandManager->executeCommand(command, args, clientSocket);
	return NULL;
}

void * Server::stop() {
	unsigned int size = connectedClients.size();
	long n;
	int message = DISCONNECT;
	//Sends a disconnection signal to all connected clients
	for (unsigned int i = 0; i < size; i++ ) {
		n = write(connectedClients[i], &message, sizeof(message));
		if (n) {
			cout << "Error: unable to send shutdown message to socket: " <<  connectedClients[i] << endl;
		}
	}
	serverOn = false;
	pthread_cancel(serverThreadId);
	close(serverSocket);
	cout << "Server stopped" << endl;
	return NULL;
}

static void * acceptClients(void * args) {
	ThreadArgs *ta =  (ThreadArgs*) args;	//Unpack thread args
											// Define the client socket's structures
	long serverSocket = ta->serverSocket;
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);
	while (true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress,&clientAddressLen);
		cout << "Client connected" << endl;
		if (clientSocket == -1) {
			throw "Error on accept";
		}
		pthread_t newThread;
		//Passes the client socket as parameter
		ta->clientSocket = clientSocket;
		int result = pthread_create(&newThread, NULL, &handleClient, (void *) ta); //Run handleClient
		if (result) {
		 cout << "Error: unable to create thread, " << result << endl;
		 exit(-1);
		}
	}
}

static void * endServer(void * args) {
	Server *trgtServer = (Server*) args;
	string stop = "";
	do {
		cout << "Enter 'stop' for closing the server." << endl;
		cin >> stop;
	} while(stop.compare("stop"));
	trgtServer->stop();
	return NULL;
}


///TODO TODO TODO - DELETE


static void *testFunction(long socket, CommandsManager *cm) {
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);
	while (true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket = accept(socket, (struct sockaddr *)&clientAddress,&clientAddressLen);
		cout << "Client connected" << endl;
		if (clientSocket == -1) {
			throw "Error on accept";
		}
		char commandStr[MAX_COMMAND_LEN];
		// Read the command from the socket
		long n = read(clientSocket, commandStr, MAX_COMMAND_LEN);
		if (n == -1) {
			cout << "Error reading command" << endl;
			return NULL;
		}
		cout << "Received command: " << commandStr << endl;
		// Split the command string to the command name and the arguments
		string str(commandStr);
		istringstream iss(str);
		string command;
		iss >> command;
		vector<string> args;
		while (iss) {
			string arg;
			iss >> arg;
			args.push_back(arg);
		}
		cout << command;
		cm->executeCommand(command, args, clientSocket);
		return NULL;
	}
}

///TODO TODO TODO - DELETE
