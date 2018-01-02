/*
 * JoinCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */

#include "JoinCommand.h"

JoinCommand::JoinCommand(GameCenter*gc) : gameCenter(gc){}

void JoinCommand::execute(vector<string> args) {
	if(!gameCenter->isInWaitingList(args[0])) {
		throw "Could not join game";
	}
	//else join...
	gameCenter->removeFromWaitingList(args[0]);
}

