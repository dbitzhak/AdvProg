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
#include <boost/serialization/access.hpp>
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
	*The output: The received user's input (int pair)
	*The function operation: Roy's function
	********************************************************/
	std::pair<int, int> getNumberFromUser();


	//Members
	const GraphicInterface *graphicProvider;

	// Allow serialization to access non-public data members
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive &ar, unsigned int version) {
	ar & graphicProvider & boost::serialization::base_object<Player>(*this);; // Serialize the data members of HumanPlayer
	}
};

#endif /* HUMANPLAYER_H_ */
