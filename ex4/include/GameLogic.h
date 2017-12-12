#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "Board.h"
#include "Player.h"
#include "Cell.h"
#include <vector>
#include <map>
#include <utility>

using namespace std;

/******************************************************
Interface - GameLogic defines the necessary functions of variations on the GameLogic
********************************************************/
class GameLogic {
public:
	virtual ~GameLogic(void) {};
	//flow control
	virtual bool  gameEnded() = 0;
	virtual void startGame(Player *p1, Player *p2) = 0; //Allows for restarting matches
	virtual Player* getWinner() = 0;
	virtual void playNextTurn() = 0;
	virtual void endGame() = 0;
	virtual Board* getBoard() const = 0;
	virtual vector<Cell> getValidPositions(Player *player, Board *gameBoard) = 0;
	virtual void convertAndSpread(Board *gameBoard, Cell start, Player *player) = 0; //Makes the move and convert the necessary enemy cells
	virtual pair<int,int> getLastPlay(void) = 0;
	virtual char getCurrentPlayerId() = 0;
	virtual void stopMatch() = 0;
private:
	// Game Play actions
	virtual bool isPositionValid(Cell c, Player *player, Board *gameBoard) = 0;
	//Can be overrided if rules are defined differently
	virtual vector<Cell> generalCheck(Board *gameBoard, Cell start, char target, int rowDif, int colDif) = 0;
};

#endif /* GAMELOGIC_H_ */
