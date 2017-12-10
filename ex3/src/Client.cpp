/*
 * Client.cpp
 *
 *  Created on: Dec 3, 2017
 *      Author: dan
 */

#include "Client.h"
#include "Board.h"
#include "Cell.h"
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <utility>
#include <string>

using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	 cout << "Client" << endl;
	}

void Client::connectToServer() {
	 // Create a socket point
	 clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	 if (clientSocket == -1) {
		 throw "Error opening socket";
	 }
	 // Convert the ip string to a network address
	 struct in_addr address;
	 if (!inet_aton(serverIP, &address)) {
		 throw "Can't parse IP address";
	 }

	 // Get a hostent structure for the given host address
	  struct hostent *server;
	  server = gethostbyname(serverIP);
	  //server = gethostbyaddr((const void *)&address, sizeof address, AF_INET);
	  if (server == NULL) {
		  throw "Host is unreachable";
	  }
	  // Create a structure for the server address
	  struct sockaddr_in serverAddress;
	  bzero((char *)&address, sizeof(address));
	  serverAddress.sin_family = AF_INET;
	  memcpy((char *)&serverAddress.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	  // htons converts values between host and network byteorders
	  serverAddress.sin_port = htons(serverPort);
	  // Establish a connection with the TCP server
	  if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
		  throw "Error connecting to server";
	  }
	  cout << "Connected to server" << endl;
	 }

void Client::sendMove(char* buffer) {
	//Sends input to Server
	long n = write(clientSocket, &buffer, sizeof(buffer));
	if (n == -1) {
		throw "Error sending player's move";
	}
}

string Client::receiveMove() {
	// Read the result from the server
	char buffer[17];
	//Fills/Empties the buffer
	for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
			buffer[j] = '\0';
	}
	long n = read(clientSocket, &buffer, sizeof(buffer));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	string move(buffer);
	return move;
}
