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

#define ERROR -5
#define SERVER_STOPPED -777
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
	
	long n = write(clientSocket, buffer, 31);
	delete[] buffer;
	
	if(n == -1) {
		throw "Error starting game\n";
	}
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		throw "Error reading result from socket\n";
	}
	if(n == 0) {
		throw SERVER_STOPPED;
	}
	if(response == -1) {
		throw "Name already taken\n";
	}
	cout << "Waiting for player to join..." << endl;
	//Get confirmation code 0 when player connects to game
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		cout << "Error reading result from socket\n";
		throw "Error reading result from socket\n";
	}
	if(n == 0) {
		return;
	} else if (n == SERVER_STOPPED){
		cout << "Server stopped\n";
		throw "Server stopped\n";
	}
}

string Client::joinGame(string name) {
	if(name.empty()) {
		char buffer[] = {'j','o','i','n','\0'};
		long n = write(clientSocket, &buffer, sizeof(buffer) + 1);
		if(n == -1) {
			throw "Error sending command join\n";
		}
		//Get string size
		int stringSize;
		n = read(clientSocket, &stringSize, sizeof(stringSize));
		if(stringSize == 0) {
			return "";
		}
		//Get string as char *
		char stringBuffer[stringSize + 1];
		n = read(clientSocket, &stringBuffer, stringSize + 1);
		//Convert to string
		string availableGames(stringBuffer);
		return availableGames;
	}
	
	char buffer[31];
	strcpy(buffer, name.c_str());
	long n = write(clientSocket, &buffer, sizeof(buffer) + 1);
	
	if (n == -1) {
		throw "Error joining game";
	}
	int response;
	//Server sends -1 if name is invalid, else 0
	n = read(clientSocket, &response, sizeof(response));
	if(n == -1) {
		throw "Error reading result from socket";
	}
	if(response == -1) {
		return "0";
	} else if(response == 0) {
		return "1";
	} else {
		return "2";
	}
}

void Client::closeGame() {
	close(clientSocket);
}

char* Client::getBuffer(string command, string args) {
	command.append(" ");
	command.append(args);
	char *buffer = new char[MSG_LIMIT];
    strcpy(buffer, command.c_str());
	return buffer;
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


pair<int,int> Client::receiveMove() {
	// Read the result from the server
	int x, y;
	
	long n = read(clientSocket, &x, sizeof(x));
	if (n == -1) {
		return make_pair(SERVER_STOPPED, SERVER_STOPPED);
	}

	if(n == 0) {
		return make_pair(SERVER_STOPPED, SERVER_STOPPED);
	}
	if(x == ERROR) {
		return make_pair(ERROR, ERROR);
	}
	
	n = read(clientSocket, &y, sizeof(y));
	if (n == -1) {
		return make_pair(SERVER_STOPPED, SERVER_STOPPED);
	}
	if(n == 0) {
		return make_pair(SERVER_STOPPED, SERVER_STOPPED);
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
