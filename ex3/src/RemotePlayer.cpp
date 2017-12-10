/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: dan
 */

#include <RemotePlayer.h>
#include <sstream>
#include <string>


RemotePlayer::RemotePlayer(GameLogic *gl, Client network, const GraphicInterface *gi, char value) : display(gi), client(network),
gameLogic(gl){
		setPlayerId(value);

}

std::pair<int, int> RemotePlayer::makeMove() {
	string strResult = client.receiveMove();
	char *temp = new char[strResult.length() + 1];
	strcpy(temp, strResult.c_str());
	pair<int,int> coordinates = convertInputToCoord(temp);
	delete [] temp;
	return coordinates;
}

void RemotePlayer::outOfPlays() {
	display->displayPlayer(this);
	display->displayMessage("\nYou are out of plays!\n");
}

pair<int, int> RemotePlayer::convertInputToCoord(char* buffer) {
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
