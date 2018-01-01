/*
 * ListGamesCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */

#include "ListGamesCommand.h"

ListGamesCommand::ListGamesCommand(GameCenter *gc) : gameCenter(gc){}

void ListGamesCommand::execute(vector<string> args) {
	for(unsigned int i = 0; i < gameList.size(); i++) {
		if(gameList[i] == args[0]) {

		}
	}
	gameList.push_back(args[0]);
	waitingList.push_back(args[0]);
}


//return a list of games that the player can join (that only one player is currently in)
list<string> ListGamesCommand::listGames() {
	return waitingList;
}

void ListGamesCommand::removeFromWaitingList(string name) {
	waitingList.remove(name);
}

