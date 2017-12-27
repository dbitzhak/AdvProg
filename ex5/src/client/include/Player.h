#ifndef PLAYER_H_
#define PLAYER_H_

#include "GraphicInterface.h"
#include <utility>
#include <utility>


class GraphicInterface; //Necessary forward declaration due to cyclic nature

/******************************************************
The Player interface/abstract Class
********************************************************/
class Player {
public:
	/******************************************************
	*Function name: ~Player()
	*The input: None
	*The output: None
	*The function operation: Destructor
	********************************************************/
	virtual ~Player() {};

	/******************************************************
	Pure virtual
	********************************************************/
	virtual std::pair<int, int> makeMove() = 0;

	/******************************************************
	*Function name: ==operator overload
	*The input: Player for comparison
	*The output: bool, true if they have the same 
	 identifying char, false otherwise
	*The function operation: char comparison
	********************************************************/
	bool operator ==(const Player &comparePlayer) const;

	/******************************************************
	*Function name: <operator overload
	*The input: Player for comparison
	*The output: bool, true if current Player's char smaller 
	 than the compared player, false otherwise
	*The function operation: char comparison
	********************************************************/
	bool operator <(const Player &comparePlayer) const;

	/******************************************************
	*Function name: getPlayerIdChar()
	*The input: None
	*The output: the Player's identifying char
	*The function operation: getter method for player's char
	********************************************************/
	char getPlayerIdChar() const;

	/******************************************************
	*Function name: setPlayerId()
	*The input: char value
	*The output: None
	*The function operation: Setter for the Player's 
	 identifying char
	********************************************************/
	void setPlayerId(char value);

	/******************************************************
	*Function name: outOfPlays()
	*The input: None
	*The output: None
	*The function operation: informs the player it is out 
	 of plays
	********************************************************/
	virtual void outOfPlays() = 0;

private:

	//Members
	char playerIdChar;
};

#endif /* PLAYER_H_ */
