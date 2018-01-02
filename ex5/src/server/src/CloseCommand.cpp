/*
 * CloseCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */

#include "CloseCommand.h"

CloseCommand::CloseCommand(GameCenter *gc) : gameCenter(gc){}

void CloseCommand::execute(vector<string> args) {
	gameCenter->removeFromGameList(args[0]);
			//close...
}
