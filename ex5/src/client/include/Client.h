#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_

#include "Player.h"
#include "GraphicInterface.h"
#include "GameLogic.h"
#include "Board.h"
#include <utility>
#include <sstream>

class Client {
public:
	Client();
	Client(const char *serverIP, int serverPort);
	void connectToServer();
	void sendMove(pair<int,int> move);
	pair<int,int> receiveMove();
	void init(const char* file);
	void startGame(string name);
	vector<string> getGameList();
	void joinGame(string name);
	void closeGame(string name);
private:
	string getIP(const char* file);
	int getPort(const char* file);
	//Members
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* INCLUDE_CLIENT_H_ */
