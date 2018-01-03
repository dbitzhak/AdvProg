#include "StartCommand.h"

StartCommand::StartCommand(GameCenter *gc) : gameCenter(gc){}

void StartCommand::execute(vector<string> args, long dstSocket) {
	if(gameCenter->isInGameList(args[0])) {
		throw "Could not add name to game list\n";
	}
	gameCenter->addToWaitingList(args[0]);
	gameCenter->addToGameList(args[0]);
	gameCenter->addToMap(args[0], dstSocket);
}

