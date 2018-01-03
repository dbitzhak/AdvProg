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
#include <fstream>



#define MSG_LIMIT 31

using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {}

Client::Client() {
	string strIP = getIP("clientconfig.txt");
	serverIP = strIP.c_str(); //Converts to char *const
	serverPort = getPort("clientconfig.txt");
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

void Client::startNewGame(string name) {
	char *buffer = getBuffer("start", name);
	int response;
	
	long n = write(clientSocket, &buffer, sizeof(buffer));
	delete[] buffer;
	
	if(n == -1) {
		throw "Error starting game\n";
	}
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		throw "Error reading result from socket\n";
	}
	if(response == -1) {
		throw "Name already taken\n";
	}
	//Get confirmation code 0 when player connects to game
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		throw "Error reading result from socket\n";
	}
	if(n == 0) {
		return;
	} else {
		throw "Wrong confirmation code\n";
	}
}

char* Client::getGameList() {
	char tmp[MSG_LIMIT] = {'l','i','s','t','_','g','a','m','e','s','\0'};
	
	long n = write(clientSocket, &tmp, sizeof(tmp));
	if(n == -1) {
		throw "Error sending command list_games\n";
	}
	//Get buffer size
	unsigned long bufferSize;
	n = read(clientSocket, &bufferSize, sizeof(bufferSize));
	//Get buffer
	char* buffer = new char[bufferSize];
	n = read(clientSocket, &(buffer), bufferSize);
	return buffer;
}

int Client::joinGame(string name) {
	char *buffer = getBuffer("join", name);

	long n = write(clientSocket, &buffer, sizeof(buffer));
	delete[] buffer;
	
	if (n == -1) {
		throw "Error joining game";
	}
	int response;
	//Server sends -1 if name is invalid, else 0
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		throw "Error reading result from socket";
	}
	return response;
}

void Client::closeGame(string name) {
	char* buffer = getBuffer("close", name);
	
	long n = write(clientSocket, &buffer, sizeof(buffer));
	delete[] buffer;
	
	if (n == -1) {
		throw "Error closing game";
	}
}

char* Client::getBuffer(string c, string n) {
	const char *command = c.c_str();
	const char *name = n.c_str();
	char *buffer = new char[MSG_LIMIT];
	int index = 0;
	
	for(int i = 0; i < c.length(); i++, index++) {
		buffer[i] = *command + i;
	}
	buffer[index] = '\0';
	buffer[++index] = ' ';
	index++;
	
	for(int i = 0; i < n.length(); i++) {
		buffer[index + i] = *name + i;
	}
	buffer[index] = '\0';
	return buffer;
}

void Client::sendMove(pair<int,int> move) {
	int index;
	char buffer[MSG_LIMIT] = {};
	if(move.first > 9) {
		buffer[0] = (char)(move.first / 10);
		buffer[1] = (char)(move.first % 10);
		buffer[2] = ',';
		index = 3;
	} else {
		buffer[0] = (char)(move.first);
		buffer[1] = ',';
		index = 2;
	}
	
	if(move.second > 9) {
		buffer[index] = (char)(move.second / 10);
		buffer[index + 1] = (char)(move.second % 10);
		buffer[index + 2] = '\0';
	} else {
		buffer[index] = (char)(move.second);
		buffer[index + 1] = '\0';
	}
	
	long n = write(clientSocket, &buffer, sizeof(buffer));
	if (n == -1) {
		throw "Error sending player's move";
	}
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

char * Client::getUserInput(char *buffer) {
	string input;
	 getline(cin, input);
	 //limit of 31 chars
	 const char *temp = input.c_str();
	 strcpy(buffer,temp);
	 return buffer;
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
