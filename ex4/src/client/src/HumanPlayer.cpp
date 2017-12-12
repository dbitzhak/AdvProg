
#include "HumanPlayer.h"
#include "GraphicInterface.h"
#include <iostream>
#include <limits>
#include <utility>
#include <sstream>

using namespace std;

HumanPlayer::HumanPlayer(GameLogic *gl, const GraphicInterface *gi, char value) :display(gi), gameLogic(gl) {
		setPlayerId(value);
}


pair<int, int> HumanPlayer::convertInputToCoord(char* buffer) {
	//Convert string to valid move
	string receivedText(buffer);
	size_t index = receivedText.find(",");
	//If no comma
	if (index == string::npos) {
		//Gets the string up to delimiter '\0'
		string message = receivedText.substr(0, receivedText.find('\0'));
	}
	//Get coordinates
	string xCoord = receivedText.substr(0,index);
	string yCoord = receivedText.substr(index+1, receivedText.find('\0'));
	//Convert to int
	stringstream xToInt(xCoord);
	stringstream yToInt(yCoord);
	int x;
	int y;
	xToInt >> x;
	yToInt >> y;
	return make_pair(x,y);
}


pair<int,int> HumanPlayer::makeMove() {
	//Get Valid Plays
	vector<Cell> validMoves;
	validMoves = gameLogic->getValidPositions(this, gameLogic->getBoard());
	//Print moves
	display->displayPlayer(this);
	display->displayMessage(": it's your move.\nYour possible moves: ");
	display->displayMoves(validMoves);
	//Creates and fills buffer
	char buffer[17];
	//Check if its valid input
	bool validChoice = false;
	pair<int,int> playerInput;
	//Waits for valid input
	while(!validChoice) {
		//Fills/Empties the buffer
		for (unsigned int j = 0; j < (sizeof(buffer)/sizeof(char)); j++) {
			buffer[j] = '\0';
		}
		display->displayMessage("\nPlease enter your move row,col: ");
		cin >> buffer;
		playerInput = convertInputToCoord(buffer);
		//Cleans buffer
		for (unsigned int i = 0; i < validMoves.size(); i++) {
			if ((validMoves[i].getXCord() == playerInput.first) && (validMoves[i].getYCord() ==  playerInput.second)) {
				validChoice = true;
				//Sends the move to the server
				return playerInput;
			}
		}
		display->displayMessage("Invalid input!\n");
	}
	return playerInput;
}

void HumanPlayer::outOfPlays() {
	display->displayPlayer(this);
	display->displayMessage("\nYou are out of plays!\n");
}
