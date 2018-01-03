#ifndef GRAPHICINTERFACE_H_
#define GRAPHICINTERFACE_H_

#include "Board.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>

class Player;


/******************************************************
 Interface - defines necessary functions for Graphic Providers
 ********************************************************/
class GraphicInterface {
public:
	virtual ~GraphicInterface() {};
	virtual void displayBoard(Board b) const = 0;
	virtual void displayMoves(std::vector<Cell> availablePositions) const = 0;
	virtual void displayMessage(std::string message) const = 0;
	virtual void displayMessage(char message) const = 0;
	virtual void displayPlayer(Player *player) const = 0;
	virtual void displayCoordinate(int a, int b) const = 0;

};

#endif /* GRAPHICINTERFACE_H_ */
