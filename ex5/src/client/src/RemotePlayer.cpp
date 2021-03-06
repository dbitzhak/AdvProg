/*
 * RemotePlayer.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: dan
 */

#include "RemotePlayer.h"
#include <sstream>
#include <string>
#define ERROR -5
#define SERVER_STOPPED -777


RemotePlayer::RemotePlayer(GameLogic *gl, Client network, const GraphicInterface *gi, char value) : display(gi), client(network),
gameLogic(gl){
		setPlayerId(value);
}

std::pair<int, int> RemotePlayer::makeMove() {
	display->displayMessage("\nWaiting for the other player...\n");
	pair<int, int> move = client.receiveMove();
	
	if (move.first == ERROR || move.first == SERVER_STOPPED) {
		gameLogic->stopMatch();
	}
	return move;
}

void RemotePlayer::outOfPlays() {
	pair<int, int> move = client.receiveMove();
	display->displayPlayer(this);
	display->displayMessage(" is out of plays!\n");
}

