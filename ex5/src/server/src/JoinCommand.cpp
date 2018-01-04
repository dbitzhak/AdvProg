#include "JoinCommand.h"

pthread_mutex_t lock;

JoinCommand::JoinCommand(GameCenter*gc) : gameCenter(gc){}

void JoinCommand::execute(vector<string> args, long dstSocket) {
	pthread_mutex_lock(&lock);
	//Get list
	vector<string> v = gameCenter->getWaitingList();
	unsigned long listSize = v.size();
	if(listSize == 0) { //If list is empty
		gameCenter->writeToClient(dstSocket, 0);
		return;
	}
	string stringBuffer = "";
	
	for(int i = 0; i < listSize; i++) {
		stringBuffer.append(v[i]);
		stringBuffer += '\n';
	}
	pthread_mutex_unlock(&lock);
	
	char buffer[sizeof(stringBuffer) - 1];
	strcpy(buffer, stringBuffer.c_str());
	
	gameCenter->writeToClient(dstSocket, sizeof(stringBuffer));
	gameCenter->writeToClient(dstSocket, buffer);
	
	//Get name
	string name = gameCenter->readStringFromClient(dstSocket);
	
	while(!gameCenter->isInWaitingList(name)) {
		gameCenter->writeToClient(dstSocket, FAILURE);
		name = gameCenter->readStringFromClient(dstSocket);
	}
	gameCenter->writeToClient(dstSocket, SUCCESS);
	gameCenter->writeToOpponent(name, SUCCESS);
	gameCenter->removeFromWaitingList(name);
	gameCenter->run(name, dstSocket);
}


