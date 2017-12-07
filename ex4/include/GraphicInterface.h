/*
 * GraphicInterface.h
 *  Author: Daniel Ben Itzhak
 *      338017437
 */

#ifndef GRAPHICINTERFACE_H_
#define GRAPHICINTERFACE_H_

#include "Board.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <boost/serialization/access.hpp>
#include <boost/serialization/vector.hpp>


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
	virtual void displayPlayer(Player *player) const = 0;
	virtual void displayCoordinate(int a, int b) const = 0;
private:
	// Allow serialization to access non-public data members
	 friend class boost::serialization::access;
	 template<class Archive>
	 void serialize(Archive &ar, unsigned int version) {
			ar & boost::serialization::base_object<GraphicInterface>(*this);; // Serialize the data members of HumanPlayer
	 };
};

#endif /* GRAPHICINTERFACE_H_ */
