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

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {}

Client::Client(): {
	serverIP(getIP("clientconfig.txt"));
	serverPort(getPort("clientconfig.txt"));
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

void Client::sendMove(pair<int,int> move) {
	//Sends input to Server
	long n = write(clientSocket, &move.first, sizeof(move.first));
	if (n == -1) {
		throw "Error sending player's move";
	}
	n = write(clientSocket, &move.second, sizeof(move.second));
	if (n == -1) {
		throw "Error sending player's move";
	}
}

int Client::receiveOrder() {
	int order;
	long n = read(clientSocket, &order, sizeof(order));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	return order;
}

pair<int,int> Client::receiveMove() {
	// Read the result from the server
	int x, y;
	
	long n = read(clientSocket, &x, sizeof(x));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	n = read(clientSocket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading result from socket";
	}
	return make_pair(x, y);
}

string Client::getIP(const char* file) {
	ifstream infile;
	
	infile.open(file);
	if (!infile) {
		cout << "error opening file";
	}
	
	char ip[13];
	infile >> ip;
	ip[12] = '\0';
	
	infile.close();
	return ip;
}

int Client::getPort(const char* file) {
	ifstream infile;
	
	infile.open(file);
	if (!infile) {
		cout << "error opening file";
	}
	
	char buffer[20], port[5];
	infile >> buffer >> port;
	port[4] = '\0';
	infile.close();
	
	stringstream s(port);
	int p = 0;
	s >> p;
	return p;
}
