/*
 * LocalPlayer.h
 *
 *  Created on: Dec 10, 2017
 *      Author: dan
 */

#ifndef INCLUDE_LOCALPLAYER_H_
#define INCLUDE_LOCALPLAYER_H_

#include "Player.h"
#include "GraphicInterface.h"
#include "Client.h"
#include "GameLogic.h"

#include <utility>
#include <iostream>

/******************************************************
Implements/Inherits the Player abstract class
********************************************************/
class LocalPlayer: public Player {

public:
	/******************************************************
	*Function name: LocalPlayer()
	*The input: Client client,GameLogic gl and GraphicInterface derived classes, char to be used to identify the Player
	*The output: LocalPlayer object
	*The function operation: Constructor
	********************************************************/
	LocalPlayer(GameLogic *gl, Client client, const GraphicInterface *gi, char value);

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
	GameLogic *gameLogic;
};



#endif /* INCLUDE_LOCALPLAYER_H_ */
