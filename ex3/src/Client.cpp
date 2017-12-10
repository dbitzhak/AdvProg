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
#include <sstream>


using namespace std;

Client::Client(const char *serverIP, int serverPort): serverIP(serverIP), serverPort(serverPort), clientSocket(0) {
	 cout << "Client" << endl;
	 display = 0;
	 gameLogic = 0;
	 //Players
	 myPlayer = 0;
	 opponentPlayer = 0;
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


int Client::sendExercise(int arg1, char op, int arg2) {
	 // Write the exercise arguments to the socket
	 long n = write(clientSocket, &arg1, sizeof(arg1));
	 if (n == -1) {
		 throw "Error writing arg1 to socket";
	 }
	 n = write(clientSocket, &op, sizeof(op));
	 if (n == -1) {
		 throw "Error writing op to socket";
	 }
	 n = write(clientSocket, &arg2, sizeof(arg2));
	 if (n == -1) {
		 throw "Error writing arg2 to socket";
	 }
	 // Read the result from the server
	 int result;
	 n = read(clientSocket, &result, sizeof(result));
	 if (n == -1) {
		 throw "Error reading result from socket";
	 }
	 return result;
}

void Client::chooseMenuOption() {
	char buffer[500]; //menu buffer
	for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
			buffer[j] = '\0';
	}
	long n = read(clientSocket, &buffer, sizeof(buffer)); //Gets menu message
	if (n == -1) {
			 throw "Error reading from menu";
	}
	this->display->displayMessage(buffer);
	//Gets player reply
	int choice;
	cin >> choice;
	while((choice > 3) && (choice < 1)) {
		this->display->displayMessage("Invalid choice, please enter a number between 1-3\n");
		cin >> choice; //Receive player's choice
	}
	n = write(clientSocket, &choice, sizeof(choice)); //Sends player's choice
	if (n == -1) {
			throw "Error writing player's choice to socket";
	}
}

void Client::playMatch() {
	//Gets the player order in the game
	int playerOrder;
	if (playerOrder == 1) {
		HumanPlayer p1(display, 'X');
		myPlayer = &p1;
		HumanPlayer p2(display,'O');
		opponentPlayer = &p2;
	} else {
		HumanPlayer p1(display, 'O');
		myPlayer = &p1;
		HumanPlayer p2(display,'X');
		opponentPlayer = &p2;
	}
	while()

}

void Client::getPlayerMove() {
	//Get Valid Plays
	vector<Cell> validMoves;
	validMoves = gameLogic->getValidPositions(myPlayer, gameLogic->getBoard());
	//If out of plays
	if (validMoves.empty()) {
		display->displayMessage("You are out of plays this turn!\n");
		char outOfMoves[] = "NoMove";
		//Sends player's out of moves
		long n = write(clientSocket, &outOfMoves, (sizeof(outOfMoves)/sizeof(char)));
			if (n == -1) {
					throw "Error writing player's choice to socket";
		}
		return;
	}
	//Display options
	display->displayPlayer(myPlayer);
	display->displayMessage("'s turn, valid plays:\n");
	display->displayMoves(validMoves);
	//	creates and fills buffer
	char buffer[17];
	for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
		buffer[j] = 'X';
	}
	//Get Player's input
	display->displayMessage("Please enter your move row,col: ");
	cin >> buffer;
	pair<int,int> playerInput = convertInputToCoord(buffer);
	//Check if its valid input
	bool validChoice = false;
	for (unsigned int i = 0; i < validMoves.size(); i++) {
		if ((validMoves[i].getXCord() == playerInput.first) && (validMoves[i].getYCord() ==  playerInput.second)) {
			validChoice = true;
		}
	}
	//Waits for valid input
	while(!validChoice) {
		//Cleans buffer
		for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
				buffer[j] = 'X';
		}
		display->displayMessage("Invalid input!\n ");
		display->displayMessage("Please enter your move row,col: ");
		cin >> buffer;
		for (unsigned int i = 0; i < validMoves.size(); i++) {
			if ((validMoves[i].getXCord() == playerInput.first) && (validMoves[i].getYCord() ==  playerInput.second)) {
				validChoice = true;
			}
		}
	}
	//Sends input to Server
	long n = write(clientSocket, &buffer, sizeof(buffer));
	if (n == -1) {
			throw "Error sending player's move";
	}
	//Makes move on Board
	makePlay(playerInput.first, playerInput.second, myPlayer);
}

void Client::printCurrentBoard() {
	display->displayMessage("Current Board:\n");
	Board *b = gameLogic->getBoard();
	display->displayBoard(*b);
}

void Client::getOpponentMove() {
	//	creates and fills buffer
	char buffer[17];
	for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
		buffer[j] = 'X';
	}
	//Gets opponent's move
	long n = read(clientSocket, &buffer, sizeof(buffer));
	if (n == -1) {
		throw "Error reading opponent's move";
	}
	pair<int,int> coordinates = convertInputToCoord(buffer);
	if ((coordinates.first < 0) || ((coordinates.second < 0))) {
		this->display->displayMessage("Player(");
		this->display->displayMessage("" + opponentPlayer->getPlayerIdChar());
		this->display->displayMessage("is out of moves\n");
	}
	makePlay(coordinates.first, coordinates.second, opponentPlayer);
}

void Client::makePlay(int xCoord, int yCoord, Player* p) {
	//Display Player's symbol
	display->displayPlayer(p);
	display->displayMessage(" played: ");
	display->displayCoordinate(xCoord, yCoord);
	//Make player's move on Board
	gameLogic->convertAndSpread(gameLogic->getBoard(), Cell(xCoord, yCoord, ' '), p);
}

pair<int, int> Client::convertInputToCoord(char* buffer) {
	//Convert string to valid move
		string receivedText(buffer);
		size_t index = receivedText.find(",");
		//If no comma
		if (index == string::npos) {
			//Gets the string up to delimiter X
			string message = receivedText.substr(0, receivedText.find("X"));
			if(message.compare("NoMove") == 0) {
				return make_pair(-1,-1);
			}
		}
		//Get coordinates
		string xCoord = receivedText.substr(0,index);
		string yCoord = receivedText.substr(index+1, receivedText.find('X'));
		//Convert to int
		stringstream xToInt(xCoord);
		stringstream yToInt(yCoord);
		int x;
		int y;
		xToInt >> x;
		yToInt >> y;
		return make_pair(x,y);
}
