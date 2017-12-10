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
#include "Serialization.h"
#include "GameLogic.h"
#include "Board.h"
#include <utility>

class Client {
	public:
	 	 Client(const char *serverIP, int serverPort);
	 	 void connectToServer();
	 	 void playMatch();
	 	 int sendExercise(int arg1, char op, int arg2);
	private:

	 	 void chooseMenuOption();
	 	 void printCurrentBoard();
	 	 void getPlayerMove();
	 	 void makePlay(int xCoord, int yCoord, Player *p);
	 	 void getOpponentMove();
	 	 //Members
	 	 const char *serverIP;
	 	 Player* myPlayer;
	 	 Player* opponentPlayer;
	 	 int serverPort;
	 	 int clientSocket;
	 	 GraphicInterface *display;
	 	 GameLogic* gameLogic;
	 	 pair<int,int> convertInputToCoord(char *buffer);
};

#endif /* INCLUDE_CLIENT_H_ */
