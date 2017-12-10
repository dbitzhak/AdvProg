/*
 * Client.h
 *
 *  Created on: Dec 3, 2017
 *      Author: dan
 */

#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_

#include "Player.h"
#include "GraphicInterface.h"
#include "GameLogic.h"
#include "Board.h"
#include <utility>

class Client {
	public:
	 	 Client(const char *serverIP, int serverPort);
	 	 void connectToServer();
	 	 void sendMove(char* buffer);
		int receiveOrder();
	 	 string receiveMove();
	private:
	 	 //Members
	 	 const char *serverIP;
	 	 int serverPort;
	 	 int clientSocket;
};

#endif /* INCLUDE_CLIENT_H_ */
