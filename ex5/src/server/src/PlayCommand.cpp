#include "PlayCommand.h"
#include <unistd.h>


PlayCommand::PlayCommand() {}

void PlayCommand::execute(vector<string> args, long dstSocket) {
	pair<int,int> move = getMove(args[0]);
	writeMove(move, dstSocket);
}

pair<int,int> PlayCommand::getMove(string arg) {
	int x, y, index;
	const char *buffer = arg.c_str();
	//Get x
	if(buffer[1] == ',') {
		x = (int)buffer[0];
		index = 2;
	} else {
		x = (int)buffer[0] * 10 + (int)buffer[1];
		index = 3;
	}
	
	//Get y
	if(buffer[index + 1] == '\0') {
		y = (int)buffer[index + 1];
	} else {
		y = (int)buffer[index + 1] * 10 + (int)buffer[index + 2];
	}
	
	return make_pair(x,y);
}

void PlayCommand::writeMove(pair<int,int> move, long dstSocket) {
	long n = write(dstSocket, &move.first, sizeof(move.first));
	if(n == -1) {
		cout << "Error writing x to socket\n";
	}
	
	n = write(dstSocket, &move.second, sizeof(move.second));
	if(n == -1) {
		cout << "Error writing y to socket\n";
	}
}




