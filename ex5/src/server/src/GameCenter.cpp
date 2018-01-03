#include "GameCenter.h"
#include <unistd.h>
#include <string>
#define MSG_LIMIT 31

void GameCenter::run(string name, long socket2) {
	long socket1 = gameToSocketMap.at(name);
	char buffer[MSG_LIMIT];
	
	long n = read((int)socket1, &buffer, sizeof(buffer));
	if(n == -1) {
		cout << "Error reading from socket\n";
	}
	
	string command = getCommand(buffer);
	vector<string> args = getArgs(buffer);
	
}

string GameCenter::getCommand(char *buffer) {
	return (string)buffer;
}

vector<string> GameCenter::getArgs(char *buffer) {
	int i;
	for(i = 0; buffer[i] != '\0'; i++) {}
	vector<string> args = {(string)(buffer + i + 1)};
	return args;
}

void GameCenter::writeToOpponent(string name, int msg) {
	long socket = gameToSocketMap.at(name);
	long n = write((int)socket, &msg, sizeof(msg));
	if(n == -1) {
		cout << "Error writing to socket\n";
	}
}

vector<string> GameCenter::getWaitingList() {
	return waitingList;
}

void GameCenter::addToWaitingList(string name) {
	for(unsigned int i = 0; i < waitingList.size(); i++) {
		if(name == waitingList[i]) {
			throw "Could not add name to waiting list";
		}
	}
	waitingList.push_back(name);
}

void GameCenter::addToGameList(string name) {
	for(unsigned int i = 0; i < gameList.size(); i++) {
		if(name == gameList[i]) {
			throw "Could not add name to game list";
		}
	}
	gameList.push_back(name);
}

void GameCenter::removeFromWaitingList(string name) {
	for(unsigned int i = 0; i < waitingList.size(); i++) {
		if(name == waitingList[i]) {
			waitingList.erase(waitingList.begin() + i);
			return;
		}
	}
	throw "Could not remove name from waiting list";
}

void GameCenter::removeFromGameList(string name) {
	for(unsigned int i = 0; i < gameList.size(); i++) {
		if(name == gameList[i]) {
			gameList.erase(gameList.begin() + i);
		}
	}
	throw "Could not remove name from game list";
}

bool GameCenter::isInGameList(string name) {
	for(unsigned int i = 0; i < gameList.size(); i++) {
		if(name == gameList[i]) {
			return true;
		}
	}
	return false;
}

bool GameCenter::isInWaitingList(string name) {
	for(unsigned int i = 0; i < waitingList.size(); i++) {
		if(name == waitingList[i]) {
			return true;
		}
	}
	return false;
}

void GameCenter::addToMap(string name, long socket) {
	gameToSocketMap[name] = socket;
}

void GameCenter::removeFromMap(string name) {
	gameToSocketMap.erase(name);
}

void GameCenter::writeToClient(int socket, int i) {
	long n = write(socket, &i, sizeof(i));
	if(n == -1) {
		throw "Error writing to socket\n";
	}
}

void GameCenter::writeToClient(int socket, char* buffer) {
	long n = write(socket, &buffer, sizeof(buffer));
	if(n == -1) {
		throw "Error writing to socket\n";
	}
}




