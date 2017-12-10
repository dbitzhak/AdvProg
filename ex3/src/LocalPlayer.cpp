/*
 * LocalPlayer.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: dan
 */

#include "LocalPlayer.h"
#include "Player.h"
#include "GraphicInterface.h"
#include "GameLogic.h"
#include <iostream>
#include <limits>
#include <utility>
#include <sstream>


LocalPlayer::LocalPlayer(GameLogic *gl, Client network, const GraphicInterface *gi, char value) : display(gi), client(network),
gameLogic(gl){
		setPlayerId(value);

}

void LocalPlayer::outOfPlays() {
	char buffer[] ="NoMove";
	client.sendMove(buffer);
}

pair<int, int> LocalPlayer::convertInputToCoord(char* buffer) {
	//Convert string to valid move
		string receivedText(buffer);
		size_t index = receivedText.find(",");
		//If no comma
		if (index == string::npos) {
			//Gets the string up to delimiter '\0'
			string message = receivedText.substr(0, receivedText.find('\0'));
			if(message.compare("NoMove") == 0) {
				return make_pair(-1,-1);
			}
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

pair<int,int> LocalPlayer::makeMove() {
	//Get Valid Plays
	vector<Cell> validMoves;
	validMoves = gameLogic->getValidPositions(this, gameLogic->getBoard());
	//	creates and fills buffer
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
		display->displayMessage("Please enter your move row,col: ");
		cin >> buffer;
		playerInput = convertInputToCoord(buffer);
		//Cleans buffer
		for (unsigned int i = 0; i < validMoves.size(); i++) {
			if ((validMoves[i].getXCord() == playerInput.first) && (validMoves[i].getYCord() ==  playerInput.second)) {
				validChoice = true;
				//Sends the move to the server
				client.sendMove(buffer);

			}
		}
		display->displayMessage("Invalid input!\n ");
	}
	return playerInput;
}
