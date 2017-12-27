#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <utility>
//using namespace std;
#define MAX_CONNECTED_CLIENTS 10
Server::Server(int port): port(port), serverSocket(0) {
 cout << "Server" << endl;
}
void Server::start() {
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
	// Start listening to incoming connections
	listen(serverSocket, MAX_CONNECTED_CLIENTS);
	// Define the client socket's structures
	struct sockaddr_in clientAddress;
	socklen_t clientAddressLen = sizeof(clientAddress);
	
	while (true) {
		cout << "Waiting for client connections..." << endl;
		// Accept a new client connection
		int clientSocket1 = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client1 connected" << endl;
		if (clientSocket1 == -1) {
			throw "Error on accept";
		}
		
		int clientSocket2 = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLen);
		cout << "Client2 connected" << endl;
		if (clientSocket2 == -1) {
			throw "Error on accept";
		}

		handleClients(clientSocket1, clientSocket2);
		// Close communication with the clients
		close(clientSocket1);
		close(clientSocket2);
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
void Server::handleClients(int clientSocket1, int clientSocket2) {
	int client1 = 1;
	int client2 = 2;
	
	//send 1 to client1
	long n = write(clientSocket1, &client1, sizeof(client1));
	if (n == -1) {
		cout << "Error writing to socket1" << endl;
		alertClient(clientSocket2);
		return;
	}
	
	//send 2 to client2
	n = write(clientSocket2, &client2, sizeof(client2));
	if (n == -1) {
		cout << "Error writing to socket2" << endl;
		alertClient(clientSocket1);
		return;
	}
	
	
	while (true) {
		// Read new move argument from client1
		pair<int,int> move;
		
		try {
			move = receiveMove(clientSocket1);
		} catch (const char *msg) { //alert both clients
			cout << msg;
//			alertClient(clientSocket1);
			alertClient(clientSocket2);
			return;
		}
		
		try {
			passMove(move, clientSocket2);
		} catch (const char *msg) {
			cout << msg;
			alertClient(clientSocket1);
			return;
		}
		
		//if game ended
		if (move.first == END || move.first == ERROR) {
			return;
		}
		
		// Read new move argument from client2
		try {
			move = receiveMove(clientSocket2);
		} catch(const char *msg) {
			cout << msg;
			alertClient(clientSocket1);
//			alertClient(clientSocket2);
			return;
		}
		try {
			passMove(move, clientSocket1);
		} catch (const char *msg) {
			cout << msg;
			alertClient(clientSocket2);
			return;
		}
		
		//if game ended
		if (move.first == END || move.first == ERROR) {
			return;
		}
	}
}


void Server::stop() {
	close(serverSocket);
}



