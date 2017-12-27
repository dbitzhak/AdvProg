#ifndef STANDARDLOGIC_H_
#define STANDARDLOGIC_H_

#include "Board.h"
#include "Cell.h"
#include "GameLogic.h"
#include "GraphicInterface.h"
#include "Player.h"
#include <vector>

using namespace std;

/******************************************************

Responsible for implementing the GameLogic functions in accordance to the StandardRules
*******************************************************/

class StandardLogic: public GameLogic {
public:
	/******************************************************
	*Function name: StandardLogic()
	*The input: GraphicInterface object
	*The output: StandardLogic object
	*The function operation: Constructor
	********************************************************/
	StandardLogic(const GraphicInterface *gi);

	/******************************************************
	*Function name: StandardLogic()
	*The input: None.
	*The output: None
	*The function operation: Destructor
	********************************************************/
	~StandardLogic();


	//Implements from GameLogic
	//flow control
	/******************************************************
	*Function name: startGame()
	*The input: two objects of base class Player
	*The output: None
	*The function operation: Starts a match between the two players, by calling the necessary functions for setting up the match
	********************************************************/
	virtual void startGame(Player *p1, Player *p2); //Allows for restarting matches

	/******************************************************
	*Function name: gameEnded()
	*The input: Non
	*The output: bool false if there are possible moves for one of the players, false otherwise.
	*The function operation: Checks if there are remaining moves.
	********************************************************/
	virtual bool  gameEnded();

	/******************************************************
	*Function name: getWinner()
	*The input: None.
	*The output: Player who won
	*The function operation: Counts the number of pieces with each
	player's char and, returns the player with the most number of pieces
	********************************************************/
	virtual Player* getWinner();

	/******************************************************
	*Function name: playNextTurn()
	*The input: None.
	*The output: None
	*The function operation: Calls the respective player to play and verifies if
	a valid move was done and passes the turn to the next Player.
	********************************************************/
	virtual void playNextTurn();

	/******************************************************
	*Function name: endGame()
	*The input: None.
	*The output: None
	*The function operation: Deletes the allocated Board
	********************************************************/
	virtual void endGame();

	/******************************************************
	*Function name: getBoard()
	*The input: None.
	*The output: Board copy
	*The function operation: Returns a copy of the Board
	********************************************************/
	virtual Board* getBoard() const;

	/******************************************************
	*Function name: getValidPositions()
	*The input: Player, the player whose valid positions we want to check, Board to be checked.
	*The output: vector<Cell>
	*The function operation: checks all the Board for valid positions
	********************************************************/
	vector<Cell> getValidPositions(Player *player, Board *gameBoard);

	/******************************************************
	*Function name: convertAndSpread()
	*The input: Target Board, start - Cell to have it's value changed Player - The player who made the move
	*The output: None
	*The function operation: Converts the Cell and calls the necessary functions
	for converting the valid pieces transformed by its change of state.
	********************************************************/
	void convertAndSpread(Board *gameBoard,Cell start,Player *player);

	/******************************************************
	*Function name: getLastPlay()
	*The input: None
	*The output: The int pair representing the last played made in terms of x,y coordinates.
	*The function operation: Returns a previously stored int pair.
	********************************************************/
	virtual pair<int,int> getLastPlay(void);


	/******************************************************
	*Function name: getCurrentPlayerId()
	*The input: None
	*The output: The char representing the current player.
	*The function operation: Returns the current player id.
	********************************************************/
	virtual char getCurrentPlayerId();


private:
	// Game Play actions


	/******************************************************
	*Function name: generalCheck()
	*The input: Board to be checked, starting Cell (position), desired direction (rowDif,colDif) and target - Player's identifier
	*The output: None
	*The function operation: Checks if from the given position there is a direct path to a player's char not obstructed by empty Cells
	********************************************************/
	//Can be overrided if rules are defined differently
	virtual vector<Cell> generalCheck(Board *gameBoard,Cell start, char target, int rowDif, int colDif);


	//Inner routines

	/******************************************************
	*Function name: isPositionValid()
	*The input: Board to be checked, Cell of the desired position, Player for which the Cell;'s validity is being checked
	*The output: bool true if valid, false otherwise.
	*The function operation: Checks if there is a direct path to a player's symbol-valued Cell, not obstructed by empty Cells
	********************************************************/
	bool isPositionValid(Cell c, Player *player, Board *gameBoard);

	/******************************************************
	*Function name: setBoard()
	*The input: None
	*The output: the allocated Board
	*The function operation: Creates a new Board on the standard
	rules size 8x8 and sets the initial positions
	********************************************************/
	Board setBoard();

	//              Directional checks

	/******************************************************
	*Function name: checkUp()
	*The input: Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell[s above the starting one
	********************************************************/
	vector<Cell> checkUp(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkDown()
	*The input:Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's down side
	********************************************************/
	vector<Cell> checkDown(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkLeft()
	*The input: Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's left side
	********************************************************/
	vector<Cell> checkLeft(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkRight()
	*The input: Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's right side
	********************************************************/
	vector<Cell> checkRight(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkDigRightUp()
	*The input: Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's up-right's diagonal
	********************************************************/
	vector<Cell> checkDigRightUp(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkDigRightDown()
	*The input: Target Board, Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's down-right's diagonal
	********************************************************/
	vector<Cell> checkDigRightDown(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkDigLeftUp()
	*The input: Target Board,Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's up-left's diagonal
	********************************************************/
	vector<Cell> checkDigLeftUp(Cell start, char target, Board *gameBoard);

	/******************************************************
	*Function name: checkDigLeftDown()
	*The input: Target Board,Starting Cell, player's symbol
	*The output: None
	*The function operation: Calls generalCheck on the Cell's down-left's diagonal
	********************************************************/
	vector<Cell> checkDigLeftDown(Cell start, char target, Board *gameBoard);

	//              Converters & Preachers

	/******************************************************
	*Function name: convertPath()
	*The input: Target Board,A Cell's vector representing a path in Board, the move player's value
	*The output: None
	*The function operation: Sets all the Cell's in the path to the player's identifying char
	********************************************************/
	void convertPath(vector<Cell> path, char value, Board *gameBoard);

	/******************************************************
	*Function name: propagateConversion()
	*The input: Target Board, Cell start, the Cell recently converted by a player
	*The output: None
	*The function operation: Looks for valid paths to Cells and then calls convertPath on them.
	********************************************************/
	void propagateConversion(Cell start, Board *gameBoard);
	
	void stopMatch();

	//Members
	Board* myBoard;
	Player* player1;
	Player *player2;
	Player *currentPlayer;
	const GraphicInterface *graphicProvider;
	int numRows;
	int numCol;
	pair<int,int> lastPlay;
	bool matchRunning;
};


#endif /* STANDARDLOGIC_H_ */
