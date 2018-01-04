#include "GameCenter.h"
#include <unistd.h>
#include <string>
#include <iostream>

#define MSG_LIMIT 31
#define CLOSE -666
#define ERROR -5

using namespace std;

pthread_mutex_t GameCenter::lock;

void GameCenter::run(string name, long socket) {
	inPlay = true;
	int dstSocket = gameToSocketMap.at(name);
	int srcSocket = socket;
	
	while (inPlay) {
		int tmp = srcSocket;
		srcSocket = dstSocket;
		dstSocket = tmp;
		playOneTurn(srcSocket, dstSocket);
	}
	
	closeClientSocket(strandedClient);
	removeFromGameList(name);
	removeFromMap(name);
}

void GameCenter::playOneTurn(int srcSocket, int dstSocket) {
	pair<int,int> move;

	// Read new move argument from srcSocket
	try {
		move = receiveMove(srcSocket);
	} catch(const char *msg) {
		cout << msg;
		endPlay(dstSocket);
		return;
	}
	
	//if game ended
	if (move.first == CLOSE || move.first == ERROR) {
		endPlay(dstSocket);
		return;
	}
	
	try {
		passMove(move, dstSocket);
	} catch (const char *msg) {
		cout << msg;
		endPlay(srcSocket);
		return;
	}
}

void GameCenter::endPlay(int socket) {
	strandedClient = socket;
	inPlay = false;
}

void GameCenter::closeClientSocket(int socket) {
	close(socket);
}

pair<int,int> GameCenter::receiveMove(int socket) {
	int x, y;
	
	// Read new move argument from client
	long n = read(socket, &x, sizeof(x));
	if (n == -1) {
		return make_pair(CLOSE, CLOSE);
	}
	if (n == 0) {
		throw "Client disconnected";
	}
	cout << "Got X from client: " << x << endl;
	
	//if game ended
	if (x == CLOSE || x == ERROR) {
		return make_pair(CLOSE, CLOSE);
	}
	
	n = read(socket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading y";
	}
	
	cout << "Got Y from client: " << y << endl;
	
	cout << "Got move from client: " << x << ", " << y << endl;
	
	return make_pair(x, y);
}

void GameCenter::passMove(pair<int,int> move, int socket) {
	long n;
	try {
		n = write(socket, &move.first, sizeof(move.first));
	} catch(exception e) {
		cout << "passMove: Error writing x to socket" << endl;
		throw "Error writing x to socket\n";
	}
	if (n == -1) {
		cout << "passMove: Error writing x to socket" << endl;
		throw "Error writing x to socket\n";
		//		return;
	}
	try {
		n = write(socket, &move.second, sizeof(move.second));
	} catch(exception e) {
		cout << "passMove: Error writing y to socket" << endl;
		throw "Error writing y to socket\n";
		//		return;
	}
	if (n == -1) {
		cout << "passMove: Error writing y to socket" << endl;
		throw "Error writing y to socket\n";
		//		return;
	}
}

void GameCenter::writeToOpponent(string name, int msg) {
	long socket = gameToSocketMap.at(name);
	long n = write(socket, &msg, sizeof(msg) + 1);
	if(n == -1) {
		cout << "Error writing to socket\n";
	}
}


string GameCenter::readStringFromClient(int socket) {
	char buffer[31];
	long n = read(socket, &buffer, sizeof(buffer) + 1);
	return (string)buffer;
}

vector<string> GameCenter::getWaitingList() {
	return waitingList;
}

void GameCenter::addToWaitingList(string name) {
	pthread_mutex_lock(&lock);
	changeWaitingListSize(name.length() + 1);
	unsigned long size = waitingList.size();
	for(unsigned int i = 0; i < size; i++) {
		if(name == waitingList[i]) {
			throw "Could not add name to waiting list";
		}
	}
	waitingList.push_back(name);
	pthread_mutex_unlock(&lock);
}

void GameCenter::addToGameList(string name) {
	pthread_mutex_lock(&lock);
	unsigned long size = gameList.size();;
	for(unsigned int i = 0; i < size; i++) {
		if(name == gameList[i]) {
			throw "Could not add name to game list";
		}
	}
	gameList.push_back(name);
	pthread_mutex_unlock(&lock);
	
}

void GameCenter::removeFromWaitingList(string name) {
	pthread_mutex_lock(&lock);
	changeWaitingListSize(-(name.length() + 1));
	unsigned long size = waitingList.size();
	for(unsigned int i = 0; i < size; i++) {
		if(name == waitingList[i]) {
			waitingList.erase(waitingList.begin() + i);
			return;
		}
	}
	pthread_mutex_unlock(&lock);
	throw "Could not remove name from waiting list";
}

void GameCenter::removeFromGameList(string name) {
	pthread_mutex_lock(&lock);
	unsigned long size = gameList.size();
	for(unsigned int i = 0; i < size; i++) {
		if(name == gameList[i]) {
			gameList.erase(gameList.begin() + i);
			return;
		}
	}
	pthread_mutex_unlock(&lock);
	throw "Could not remove name from game list";
}

bool GameCenter::isInGameList(string name) {
	pthread_mutex_lock(&lock);
	unsigned long size = gameList.size();
	for(unsigned int i = 0; i < size; i++) {
		if(name == gameList[i]) {
			pthread_mutex_unlock(&lock);
			return true;
		}
	}
	pthread_mutex_unlock(&lock);
	return false;
}

bool GameCenter::isInWaitingList(string name) {
	pthread_mutex_lock(&lock);
	unsigned long size = waitingList.size();
	for(unsigned int i = 0; i < size; i++) {
		if(name == waitingList[i]) {
			pthread_mutex_unlock(&lock);
			return true;
		}
	}
	pthread_mutex_unlock(&lock);
	return false;
}

void GameCenter::addToMap(string name, long socket) {
	gameToSocketMap[name] = socket;
}

void GameCenter::removeFromMap(string name) {
	pthread_mutex_lock(&lock);
	gameToSocketMap.erase(name);
	pthread_mutex_unlock(&lock);
}

unsigned long GameCenter::getWaitingListSize() {
	return waitingListSize;
}

void GameCenter::changeWaitingListSize(int diff) {
	waitingListSize += diff;
}

void GameCenter::writeToClient(int socket, int i) {
	long n = write(socket, &i, sizeof(i));
	if(n == -1) {
		throw "Error writing to socket\n";
	}
}

void GameCenter::writeToClient(int socket, char* buffer) {
	cout << buffer << endl;
	cout << getWaitingListSize() << endl;
	long n = write(socket, buffer, getWaitingListSize());
	if(n == -1) {
		throw "Error writing to socket\n";
	}
}





