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

class Client {
	public:
	 	 Client(const char *serverIP, int serverPort);
	 	 void connectToServer();
	 	 void chooseMenuOption();
	 	 void playMatch();
	private:
	 	 bool makePlay();
	 	 void getOpponentPlay();
	 	 const char *serverIP;
	 	 int serverPort;
	 	 int clientSocket;
	 	 GraphicInterface *display;
	 	 Player *humanPlayer; //The Player

};

#endif /* INCLUDE_CLIENT_H_ */
