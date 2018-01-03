#include "StartCommand.h"

StartCommand::StartCommand(GameCenter *gc) : gameCenter(gc){}

void StartCommand::execute(vector<string> args, long dstSocket) {
	if(gameCenter->isInGameList(args[0])) {
		gameCenter->writeToClient((int)dstSocket, -1);
		cout << args[0] << "Could not add name to game list" << endl;
		throw "Could not add name to game list\n";
	}
	cout << "Got " << args[0] << endl;
	gameCenter->addToWaitingList(args[0]);
	gameCenter->addToGameList(args[0]);
	gameCenter->addToMap(args[0], dstSocket);
}

