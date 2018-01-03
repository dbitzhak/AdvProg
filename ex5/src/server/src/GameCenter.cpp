#include "GameCenter.h"
#include <unistd.h>
#include <string>
#include <iostream>

#define MSG_LIMIT 31
#define CLOSE -666

using namespace std;

pthread_mutex_t GameCenter::lock;

void GameCenter::run(string name, long socket2) {
	long socket1 = gameToSocketMap.at(name);
	char buffer[MSG_LIMIT];
	
	long n = read((int)socket1, &buffer, sizeof(buffer));
	if(n == -1) {
		cout << "Error reading from socket\n";
	}
	
	bool running = true;
	
	while (running) {
		// Read new move argument from client1
		pair<int,int> move;
		
		try {
			move = receiveMove(socket1);
		} catch (const char *msg) { //alert both clients
			cout << msg;
			//			alertClient(clientSocket1);
			alertClient(clientSocket2);
			return;
		}
		
		try {
			passMove(move, clientSocket2);
		} catch (const char *msg) {
			cout << msg;
			alertClient(clientSocket1);
			return;
		}
		
		//if game ended
		if (move.first == END || move.first == ERROR) {
			return;
		}
		
		// Read new move argument from client2
		try {
			move = receiveMove(clientSocket2);
		} catch(const char *msg) {
			cout << msg;
			alertClient(clientSocket1);
			//			alertClient(clientSocket2);
			return;
		}
		try {
			passMove(move, clientSocket1);
		} catch (const char *msg) {
			cout << msg;
			alertClient(clientSocket2);
			return;
		}
		
		//if game ended
		if (move.first == END || move.first == ERROR) {
			return;
		}
	}
}

pair<int,int> GameCenter::receiveMove(int socket) {
	int x, y;
	
	// Read new move argument from client
	long n = read(socket, &x, sizeof(x));
	if (n == -1) {
		throw "Error reading x";
	}
	if (n == 0) {
		throw "Client disconnected";
	}
	n = read(socket, &y, sizeof(y));
	if (n == -1) {
		throw "Error reading y";
	}
	
	cout << "Got move from client: " << x << ", " << y << endl;
	
	return make_pair(x, y);
	
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
	pthread_mutex_lock(&lock);
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



