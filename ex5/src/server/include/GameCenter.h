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
#define TRY_AGAIN 10

using namespace std;

class GameCenter {
public:
	void run(string name, long socket2);

	vector<string> getWaitingList();

	void addToWaitingList(string name);

	void addToGameList(string name);

	void removeFromWaitingList(string name);

	void removeFromGameList(string name);
	
	bool isInGameList(string name);
	
	bool isInWaitingList(string name);
	
	unsigned long getWaitingListSize();
	
	void changeWaitingListSize(int diff);
	
	void addToMap(string name, long socket);
	
	void removeFromMap(string name);
	
	void writeToClient(int socket, int i);
	
	void writeToClient(int socket, char* buffer);
	
	void writeToOpponent(string name, int msg);
	
	string readStringFromClient(int socket);
private:
	pair<int,int> receiveMove(int socket);
	void passMove(pair<int,int> move, int socket);
	void closeClientSocket(int socket);
	void playOneTurn(int srcSocket, int dstSocket);
	void endPlay(int socket);
	bool inPlay;
	int strandedClient;
	vector<string> gameList;
	vector<string> waitingList;
	unsigned long waitingListSize;
	map<string, long> gameToSocketMap;
	static pthread_mutex_t lock;
};

#endif /* GameCenter_h */

