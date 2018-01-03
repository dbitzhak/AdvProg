#include "JoinCommand.h"

JoinCommand::JoinCommand(GameCenter*gc) : gameCenter(gc){}

void JoinCommand::execute(vector<string> args, long dstSocket) {
	string name = args[0];
	if(!gameCenter->isInWaitingList(name)) {
		throw "Could not join game";
	}
	gameCenter->writeToOpponent(name, SUCCESS);
	gameCenter->removeFromWaitingList(name);
}

