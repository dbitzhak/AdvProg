#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"
#include "GraphicInterface.h"
#include "GameLogic.h"
#include <utility>
#include <iostream>

/******************************************************
Implements/Inherits the Player abstract class
********************************************************/
class HumanPlayer: public Player {
public:
	HumanPlayer();
	/******************************************************
	*Function name: HumanPlayer()
	*The input: GameLogic, GraphicInterface derived class, 
	 char to be used to identify the Player
	*The output:HumanPlayer()
	*The function operation: Constructor
	********************************************************/
	HumanPlayer(GameLogic *gl, const GraphicInterface *gi, char value);

	/******************************************************
	*Function name: makeMove()
	*The input: None
	*The output: A pair of integers
	*The function operation: Uses subroutines to receive 
	 user input
	********************************************************/
	std::pair<int,int> makeMove();
	
	/******************************************************
	 *Function name: convertInputToCoord()
	 *The input: A pair of ints as a char*
	 *The output: A pair of integers
	 *The function operation: Parses buffer to return pair
	  of ints
	 ********************************************************/
	pair<int, int> convertInputToCoord(char* buffer);

private:
	//makeMove subroutines

	/******************************************************
	*Function name: outOfPlays()
	*The input: None
	*The output: None
	*The function operation: informs the player it is out 
	 of plays
	********************************************************/
	virtual void outOfPlays();

	//Members
	const GraphicInterface *display;
	GameLogic *gameLogic;
	
};

#endif /* HUMANPLAYER_H_ */
