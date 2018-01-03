#ifndef CONSOLEGRAPHICS_H_
#define CONSOLEGRAPHICS_H_

#include "GraphicInterface.h"
#include "Player.h"
#include <vector>

#include <iostream>

/******************************************************
 *
 * Prints the contents to the Console
 * ********************************************************/
class ConsoleGraphics: public GraphicInterface {
public:

	/******************************************************
	*Function name: ConsoleGraphics()
	*The input: None.
	*The output: ConsoleGraphics object
	*The function operation: Constructor
	********************************************************/
	ConsoleGraphics(void);

	/******************************************************
	*Function name: ~ConsoleGraphics()
	*The input: None.
	*The output: None
	*The function operation: Destructor
	********************************************************/
	~ConsoleGraphics(void);

	/******************************************************
	*Function name: displayBoard()
	*The input: Board
	*The output: None
	*The function operation: Prints the Board's Cells in a 
	 defined Board format
	********************************************************/
	virtual void displayBoard(Board b) const;

	/******************************************************
	*Function name: displayMoves()
	*The input: a vector of Cells with the valid moves
	*The output: None
	*The function operation: Prints the vector's Cells in a
	 defined coordinate format
	********************************************************/
	virtual void displayMoves(std::vector<Cell> availablePositions) const;

	/******************************************************
	*Function name: displayMessage()
	*The input: a string
	*The output: None
	*The function operation: Prints the string through cout
	********************************************************/
	virtual void displayMessage(std::string message) const;

	/******************************************************
	 *Function name: displayMessage()
	 *The input: a char
	 *The output: None
	 *The function operation: Prints the char through cout
	 ********************************************************/
	virtual void displayMessage(char message) const;
	
	/******************************************************
	*Function name: displayPlayer()
	*The input: Player
	*The output: None
	*The function operation: Prints the Player identifier char 
	 in a defined format.
	********************************************************/
	virtual void displayPlayer(Player *player) const;

	/******************************************************
	*Function name: displayCoordinates
	*The input: int coordX, int coordY
	*The output: None
	*The function operation: Prints the number in a 
	 determined coordinate format
	********************************************************/
	virtual void displayCoordinate(int a, int b) const;


};

#endif /* CONSOLEGRAPHICS_H_ */
