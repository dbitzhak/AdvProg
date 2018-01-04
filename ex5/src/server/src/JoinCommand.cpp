#include "JoinCommand.h"
#include <string.h>

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
	
	int i;
	for(i = 0; i < listSize - 1; i++) {
		stringBuffer.append(v[i]);
//		stringBuffer.append("\n");
		stringBuffer += '\n';
	}
	stringBuffer.append(v[i]);
	
	pthread_mutex_unlock(&lock);
	
	char buffer[sizeof(stringBuffer)];
	strcpy(buffer, stringBuffer.c_str());
	cout << "buffer sent: " << buffer << endl;
	//Write length of list
	gameCenter->writeToClient(dstSocket, stringBuffer.length());
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

