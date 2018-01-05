#ifndef GameCenter_h
#define GameCenter_h
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <utility>

#define SUCCESS 0
#define FAILURE -1
#define TRY_AGAIN 10

using namespace std;

class GameCenter {
public:
	/********************************************************************
	 *Function name: run()
	 *The input: int socket number of the player who joined the game, name - the game to be started
	 *The output: None
	 *The function operation: Starts the game loop, between the socket
	 * address which created the game and the socket address that joined it
	 *********************************************************************/
	void run(string name, long socket2);

	/********************************************************************
	 *Function name: getWaitingList()
	 *The input: None
	 *The output: Returns a vector<string> the waiting list
	 *The function operation: Getter for the waitingList
	 *********************************************************************/
	vector<string> getWaitingList();

	/********************************************************************
	 *Function name: addToWaitingList()
	 *The input: name - the game
	 *The output: void
	 *The function operation: Adds the game to the waiting list
	 *********************************************************************/
	void addToWaitingList(string name);

	/********************************************************************
	 *Function name: addToGameList()
	 *The input: name - the game
	 *The output: void
	 *The function operation: Adds the game to the game list
	 *********************************************************************/
	void addToGameList(string name);

	/********************************************************************
	 *Function name: removeFromWaitingist()
	 *The input: name - the game
	 *The output: void
	 *The function operation: Removes the game from the waiting list
	 *********************************************************************/
	void removeFromWaitingList(string name);

	/********************************************************************
	 *Function name: removeFromGameList()
	 *The input: name - the game
	 *The output: void
	 *The function operation: Removes the game from the game list
	 *********************************************************************/
	void removeFromGameList(string name);
	
	/********************************************************************
	 *Function name: isInGameList()
	 *The input: name - game to be searched
	 *The output: true if the game is in the list, false otherwise
	 *The function operation: Parses through the list looking for a match, if it finds returns true else returns false
	 *********************************************************************/	
	bool isInGameList(string name);

	/********************************************************************
	 *Function name: isInWaitingList()
	 *The input: name - game to be searched
	 *The output: true if the game is in the waiting list, false otherwise
	 *The function operation: Parses through the list looking for a match, if it finds returns true else returns false
	 *********************************************************************/	
	bool isInWaitingList(string name);

	/********************************************************************
	 *Function name: getWaitingListSize()
	 *The input: None
	 *The output: unsigned long
	 *The function operation: Getter method for the waitingListSize
	 *********************************************************************/	
	unsigned long getWaitingListSize();

	/********************************************************************
	 *Function name: changeWaitingListSize()
	 *The input: int size to be added to the waitingListSize
	 *The output: void
	 *The function operation: Increases the waitingListSize by the diff
	 *********************************************************************/
	void changeWaitingListSize(int diff);

	/********************************************************************
	 *Function name: addToMap()
	 *The input: int socket address, name - the game to be added
	 *The output: None
	 *The function operation: Adds the game name to the list of games and associates it to the socket
	 *********************************************************************/
	void addToMap(string name, long socket);
	
	/********************************************************************
	 *Function name: removeFromMap()
	 *The input: name - the game to be removed
	 *The output: void
	 *The function operation: Removes the game with the matching name from the map
	 *********************************************************************/
	void removeFromMap(string name);
	
	/********************************************************************
	 *Function name: writeToClient()
	 *The input: int the target socket number, int the value to be sent
	 *The output: void
	 *The function operation: Sends the int value to the given socket address
	 *********************************************************************/
	void writeToClient(int socket, int i);
	
	/********************************************************************
	 *Function name: writeToClient()
	 *The input: int the target socket number, a pointer to a char array
	 *The output: void
	 *The function operation: Sends the char buffer contents to the given socket address
	 *********************************************************************/
	void writeToClient(int socket, char* buffer, int bufferSize);
	
	/********************************************************************
	 *Function name: writeToOpponent()
	 *The input: string - name of the game, int value to be sent to opponent in given game
	 *The output: void
	 *The function operation: Sends the int to the opponent's socket address
	 *********************************************************************/
	void writeToOpponent(string name, int msg);
	
	/********************************************************************
	 *Function name: readStringFromClient()
	 *The input: int representing the socket number
	 *The output: string
	 *The function operation: Reads the char array sent from the socket address and returns it as a string
	 *********************************************************************/
	string readStringFromClient(int socket);

private:
	/********************************************************************
	 *Function name: receiveMove()
	 *The input: int socket
	 *The output:  pair<int,int>
	 *The function operation: Receives the pair of ints, one by one from the socket address
	 *********************************************************************/
	pair<int,int> receiveMove(int socket);

	/********************************************************************
	 *Function name: passMove()
	 *The input: int socket, pair<int,int>
	 *The output: None
	 *The function operation: Sends the ints, one by one to the socket address
	 *********************************************************************/
	void passMove(pair<int,int> move, int socket);

	/********************************************************************
	 *Function name: closeClientSocket()
	 *The input: int socket number
	 *The output: None
	 *The function operation: Closes the socket
	 *********************************************************************/
	void closeClientSocket(int socket);

	/********************************************************************
	 *Function name: playOneTurn()
	 *The input: two ints - the target socket number, the source socket number
	 *The output: void
	 *The function operation: Receives a move from the srcScoket and passes it to the dstSocket
	 *********************************************************************/
	void playOneTurn(int srcSocket, int dstSocket);

	/********************************************************************
	 *Function name: endPlay()
	 *The input: int representing the client's socket number
	 *The output: None
	 *The function operation: Signs that the game ended
	 *********************************************************************/
	void endPlay(int socket);

	//Members
	bool inPlay;
	int strandedClient;
	vector<string> gameList;
	vector<string> waitingList;
	unsigned long waitingListSize;
	map<string, long> gameToSocketMap;
	static pthread_mutex_t lock;
};

#endif /* GameCenter_h */

