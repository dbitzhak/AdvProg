#ifndef INCLUDE_CLIENT_H_
#define INCLUDE_CLIENT_H_

#include "Player.h"
#include "GraphicInterface.h"
#include "GameLogic.h"
#include "Board.h"
#include <utility>
#include <sstream>

class Client {
public:
	/********************************************************************
	 *Function name: Client()
	 *The input: None
	 *The output: Client object
	 *The function operation: Constructor
	 *********************************************************************/
	Client();
	
	/********************************************************************
	 *Function name: Client()
	 *The input: const char* serverIP (a string representing server info), int serverPort number
	 *The output: Client object
	 *The function operation: Constructor
	 *********************************************************************/
	Client(const char *serverIP, int serverPort);
	
	/********************************************************************
	 *Function name: connectToServer()
	 *The input: None
	 *The output: None
	 *The function operation: Establishes a connection between the remote server and the local client
	 *********************************************************************/
	void connectToServer();
	
	/********************************************************************
	 *Function name: sendMove()
	 *The input: A pair of ints representing row and column coordinates
	 *The output: None
	 *The function operation: Sends the ints one at a time to the Server
	 *********************************************************************/
	void sendMove(pair<int,int> move);
	
	/********************************************************************
	 *Function name: receiveOrder()
	 *The input: None
	 *The output: An int representing the player's order in the game
	 *The function operation: Receives an int from the Server
	 *********************************************************************/
	int receiveOrder();
	
	/********************************************************************
	 *Function name: receiveOrder()
	 *The input: None
	 *The output: A pair of ints representing row and column coordinates.
	 *The function operation: Receives from the Server two ints and returns their pair
	 *********************************************************************/
	pair<int,int> receiveMove();
	
	/********************************************************************
	 *Function name: init()
	 *The input: The file name
	 *The output: Void
	 *The function operation:
	 *********************************************************************/
	void init(const char* file);
	
	/********************************************************************
	 *Function name: joinGame()
	 *The input: Name of game to join
	 *The output: Void
	 *The function operation: Tells server that client wants to join game "name"
	 *********************************************************************/
	string joinGame(string name);
	
	/********************************************************************
	 *Function name: closeGame()
	 *The input: Name of game to close
	 *The output: Void
	 *The function operation: Tells server that client is ending the game
	 *********************************************************************/
	void closeGame();
	
	/********************************************************************
	 *Function name:
	 *The input:
	 *The output:
	 *The function operation:
	 *********************************************************************/
	void startNewGame(string name);
	
	/********************************************************************
	 *Function name:
	 *The input:
	 *The output:
	 *The function operation:
	 *********************************************************************/
	string getGameList();
	
	int getNumberOfGames();
private:
	/********************************************************************
	 *Function name: getUserInput()
	 *The input: Array of chars
	 *The output: 
	 *The function operation:
	 *********************************************************************/
	char* getUserInput(char *buffer);
	
	char* getBuffer(string command, string name);
	
	/********************************************************************
	 *Function name:
	 *The input:
	 *The output:
	 *The function operation:
	 *********************************************************************/
	string getIP(const char* file);
	
	/********************************************************************
	 *Function name:
	 *The input:
	 *The output:
	 *The function operation:
	 *********************************************************************/
	int getPort(const char* file);
	//Members
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* INCLUDE_CLIENT_H_ */
