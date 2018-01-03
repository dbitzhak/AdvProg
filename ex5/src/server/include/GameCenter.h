
#ifndef GameCenter_h
#define GameCenter_h
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <utility>

#define SUCCESS 0
#define FAILURE -1

using namespace std;

class GameCenter {
public:
	void run(string name, long socket1, long socket2);
	
	vector<string> getWaitingList();
	
	void addToWaitingList(string name);
	
	void addToGameList(string name);
	
	void removeFromWaitingList(string name);
	
	void removeFromGameList(string name);
	
	bool isInGameList(string name);
	
	bool isInWaitingList(string name);
	
	void addToMap(string name, long socket);
	
	void removeFromMap(string name);
	
	void writeToClient(int socket, int i);
	
	void writeToClient(int socket, char* buffer);
	
	void writeToOpponent(string name, int msg);
private:
	string getCommand(char *buffer);
	vector<string> getArgs(char *buffer);
	vector<string> gameList;
	vector<string> waitingList;
	map<string, long> gameToSocketMap;
};

#endif /* GameCenter_h */
