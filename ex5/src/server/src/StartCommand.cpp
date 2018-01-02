/*
 * StartCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */




#include "StartCommand.h"

StartCommand::StartCommand(GameCenter *gc) : gameCenter(gc){}

void StartCommand::execute(vector<string> args) {
	if(gameCenter->isInGameList(args[0])) {
				throw "Could not add name to game list";
	}
	gameCenter->addToWaitingList(args[0]);
	gameCenter->addToGameList(args[0]);
}

