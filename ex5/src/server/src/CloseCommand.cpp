#include "CloseCommand.h"

CloseCommand::CloseCommand(GameCenter *gc) : gameCenter(gc){}

void CloseCommand::execute(vector<string> args, long dstSocket) {
	string name = args[0];
	gameCenter->removeFromGameList(name);
	gameCenter->removeFromMap(name);
}
