#ifndef GAME_H_
#define GAME_H_

#include "GameLogic.h"
#include "GraphicInterface.h"
#include "Client.h"

/******************************************************
GameClass, object that holds the necessary members for running Games,
as well as controlling their flow
********************************************************/
class Game {
public:
	//Methods

	/******************************************************
	*Function name: Game()
	*The input: GraphicInterface derived class
	*The output: Game object
	*The function operation: Constructor
	********************************************************/
	Game(GraphicInterface *gi);

	/******************************************************
	*Function name: start()
	*The input: None
	*The output:None
	*The function operation: Starts the game loop
	********************************************************/
	void start();

	/******************************************************
	*Function name: setGraphicProvider()
	*The input: GraphicInterface derived class
	*The output:None
	*The function operation: Setter for the Graphic Provider
	********************************************************/
	void setGraphicProvider(const GraphicInterface *graphicProvider);

private:
	/******************************************************
	*Function name: playOneMatch()
	*The input: GameLogic derived class,two Player's derived objects
	*The output:None
	*The function operation: Starts the match loop, for the specific players and GameLogic derived class
	********************************************************/
	void playOneMatch(GameLogic* gl, Player* p1, Player* p2);
	
	/******************************************************
	*Function name: startGame
	*The input: Client localClient, the local connected Client
	*The output: None
	*The function operation: Starts a new game with the user given name
	* and waits for another user to chose the created game, connecting them through the Client.
	********************************************************/
	void startGame(Client localClient);
	

	/******************************************************
	*Function name: joinGame
	*The input: Client localClient, the local connected Client
	*The output: None
	*The function operation: Prints a list of the available games and connects the user to the chosen one via the Client.
	********************************************************/
	void joinGame(Client localClient);

	/********************************************************************
	 *Function name: getIP
	 *The input: None
	 *The output: int the IP value written in the file
	 *The function operation: Opens the desigated hardcoded relative path of the configuration file and retuns the specified IP number
	 *********************************************************************/
	string getIP();

	/********************************************************************
	 *Function name: getPort
	 *The input: None
	 *The output: int the port value written in the file
	 *The function operation: Opens the desigated hardcoded relative path of the configuration file and retuns the specified port number
	 *********************************************************************/
	int getPort();

	// Unimplemented - void startOver(); //restarts match
	//Members
	const GraphicInterface *graphicProvider;

};

#endif /* GAME_H_ */
