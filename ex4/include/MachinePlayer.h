/*
 * MachinePlayer.h
 *
 *  Created on: Nov 18, 2017
 *      Author: dan
 */

#ifndef MACHINEPLAYER_H_
#define MACHINEPLAYER_H_

#include "Player.h"
#include "GameLogic.h"

class MachinePlayer: public Player {
public:

	/******************************************************
	*Function name: MachinePlayer()
	*The input: GameLogic in use, GraphicInterface derived class, char to be used to identify the Player
	*The output:MachinePlayer()
	*The function operation: Constructor
	********************************************************/
	MachinePlayer(GameLogic *gl, const GraphicInterface *gi, char value);



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
	*Function name: findBestMove()
	*The input: None
	*The output: Return a pair of integers
	*The function operation: For each of the possible moves simulates all the possible answers from the opponent
	********************************************************/
	std::pair<int,int>findBestMove();

	/******************************************************
	*Function name: countEnemyCells()
	*The input: Board, opponent player
	*The output: Return the total number of enemy Cells
	*The function operation: Parses through the Board counting Cells
	********************************************************/
	int countEnemyCells(Board b, Player *enemy);

	/******************************************************
	*Function name: findOpponentMaxCells()
	*The input: Board
	*The output: Return the total number of enemy Cells in their best play
	*The function operation: Simulates every possible answer and counts their results
	********************************************************/
	int findOpponentMaxCells(Board targetBoard);

	/******************************************************
	*Function name: outOfPlays()
	*The input: None
	*The output: None
	*The function operation: informs the player it is out of plays
	********************************************************/
	virtual void outOfPlays();


	//Members
	const GraphicInterface *graphicProvider;
	GameLogic *currentGameLogic;
};

#endif /* MACHINEPLAYER_H_ */
