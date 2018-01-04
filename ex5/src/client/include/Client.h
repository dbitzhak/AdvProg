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
	 *The input: None
	 *The output: Void
	 *The function operation: Closes the client socket
	 *********************************************************************/
	void closeGame();
	
	/********************************************************************
	 *Function name: startNewGame
	 *The input: string nameofthe new gametobe opened
	 *The output: None
	 *The function operation: Opens a new entry for the chosen name and waits until another
	 * player connect to it for starting the game
	 *********************************************************************/
	void startNewGame(string name);
	
	/********************************************************************
	 *Function name: getGameList
	 *The input: None
	 *The output: None
	 *The function operation: Retrieves the current game list and prints it
	 *********************************************************************/
	string getGameList();
	
	/********************************************************************
	 *Function name: getNumberOfGames
	 *The input: None
	 *The output: int the number of open games
	 *The function operation: Retrieves the current game list size and returns it
	 *********************************************************************/
	int getNumberOfGames();

private:
	/********************************************************************
	 *Function name: getUserInput
	 *The input: Array of chars
	 *The output: Returns the received buffer
	 *The function operation: Stores user input inside the passed buffer
	 *********************************************************************/
	char* getUserInput(char *buffer);
	
	/********************************************************************
	 *Function name: getBuffer
	 *The input: 2 strings - a command and its arguments
	 *The output: Returns the allocated buffer address
	 *The function operation: Appends both stringsand copies themto a char * buffer
	 *********************************************************************/
	char* getBuffer(string command, string name);
	
	/********************************************************************
	 *Function name: getIP
	 *The input: const char* file - a char array (string) representing the configuration filename
	 *The output: int the IP value written in the file
	 *The function operation: Opens the desigated configuration file and retuns the specified IP number
	 *********************************************************************/
	string getIP(const char* file);
	
	/********************************************************************
	 *Function name: getPort
	 *The input: const char* file - a char array (string) representing the configuration filename
	 *The output: int the port value written in the file
	 *The function operation: Opens the desigated configuration file and retuns the specified port number
	 *********************************************************************/
	int getPort(const char* file);
	
	//Members
	const char *serverIP;
	int serverPort;
	int clientSocket;
};

#endif /* INCLUDE_CLIENT_H_ */
