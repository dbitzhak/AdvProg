#include "JoinCommand.h"

JoinCommand::JoinCommand(GameCenter*gc) : gameCenter(gc){}

void JoinCommand::execute(vector<string> args, long dstSocket) {
	if(gameCenter->getWaitingListSize() == 0) {
		gameCenter->writeToClient(dstSocket, 0);
		return;
	}
	unsigned long listSize = gameCenter->getWaitingListSize();
	gameCenter->writeToClient(dstSocket, listSize);
	char *buffer = new char[listSize];
	
	vector<string> v = gameCenter->getWaitingList();
	long vectorSize = v.size();
	string stringBuffer;
	
	int i;
	for(i = 0; i < vectorSize - 1; i++) {
		stringBuffer.append(v[i]);
		stringBuffer += '\n';
	}
	stringBuffer.append(v[i]);
	strcpy(buffer, stringBuffer.c_str());
	buffer[listSize - 1] = '\0';
	gameCenter->writeToClient(dstSocket, buffer);
	
	
	string name = gameCenter->readStringFromClient(dstSocket);
	
	while(!gameCenter->isInWaitingList(name)) {
		gameCenter->writeToClient(dstSocket, FAILURE);
		name = gameCenter->readStringFromClient(dstSocket);
	}
	
	gameCenter->writeToOpponent(name, SUCCESS);
	gameCenter->removeFromWaitingList(name);
	gameCenter->run(name, dstSocket);
}

