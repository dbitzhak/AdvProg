/*
 * RemotePlayer.h
 *
 *  Created on: Dec 10, 2017
 *      Author: dan
 */

#ifndef INCLUDE_REMOTEPLAYER_H_
#define INCLUDE_REMOTEPLAYER_H_

#include "Player.h"
#include "GameLogic.h"
#include "GraphicInterface.h"
#include "Client.h"
#include <iostream>
#include <limits>
#include <utility>

class RemotePlayer: public Player {
public:
	/******************************************************
	*Function name: LocalPlayer()
	*The input: GameLogic gl, GraphicInterface gi, Client client, char to be used to identify the Player
	*The output: RemotePlayer()
	*The function operation: Constructor
	********************************************************/
	RemotePlayer(GameLogic *gl, Client network, const GraphicInterface *gi, char value);

	/******************************************************
	*Function name: makeMove()
	*The input: None
	*The output: A pair of integers
	*The function operation: Uses subroutines to receive user input and send it through the network
	********************************************************/
	std::pair<int,int> makeMove();

private:
	/******************************************************
	*Function name: outOfPlays()
	*The input: None
	*The output: None
	*The function operation: Informs the player it is out of plays
	********************************************************/
	virtual void outOfPlays();


	pair<int, int> convertInputToCoord(char* buffer);
	//Members
	const GraphicInterface *display;
	Client client;
	GameLogic* gameLogic;
};

#endif /* INCLUDE_REMOTEPLAYER_H_ */
