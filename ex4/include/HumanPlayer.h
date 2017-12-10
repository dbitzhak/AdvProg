/*
 * HumanPlayer.h
 *  Author: Daniel Ben Itzhak
 *      338017437
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "Player.h"
#include "GraphicInterface.h"
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
	*The input: GraphicInterface derived class, char to be used to identify the Player
	*The output:HumanPlayer()
	*The function operation: Constructor
	********************************************************/
	HumanPlayer(const GraphicInterface *gi, char value);

	/******************************************************
	*Function name: makeMove()
	*The input: None
	*The output: A pair of integers
	*The function operation: Uses subroutines to receive user input
	********************************************************/
	std::pair<int,int> makeMove();

private:
	//makeMove subroutines

	/******************************************************
	*Function name: receivePlayerInput()
	*The input: None
	*The output: Return a pair of integers
	*The function operation: Calls getNumberFromUser twice
	********************************************************/
	std::pair<int,int>receivePlayerInput();

	/******************************************************
	*Function name: getNumberFromUser()
	*The input: None (Receives user input)
	*The output: The received user's input (int)
	*The function operation: Roy's function
	********************************************************/
	int getNumberFromUser();
	
	/******************************************************
	*Function name: outOfPlays()
	*The input: None
	*The output: None
	*The function operation: informs the player it is out of plays
	********************************************************/
	virtual void outOfPlays();


	//Members
	const GraphicInterface *graphicProvider;
	
};

#endif /* HUMANPLAYER_H_ */
