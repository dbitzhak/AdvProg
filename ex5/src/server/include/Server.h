#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#define ERROR -5
#define END -666

#include "CommandsManager.h"
#include <utility>
#include <vector>
#include <pthread.h>

using namespace std;


//Server class
class Server {
public:
	/********************************************************************
	 *Function name: Server()
	 *The input: int representing the port number, CommandsManager to manage the received commands.
	 *The output: Server object
	 *The function operation: Constructor
	 *********************************************************************/
	Server(int port, CommandsManager *cm);
	
	/********************************************************************
	 *Function name: start()
	 *The input: None
	 *The output: None
	 *The function operation: Starts listening for input through a socket
	 * and waits for players to connect.
	 *********************************************************************/
	void start();
	
	/********************************************************************
	 *Function name: stop()
	 *The input: None
	 *The output: None
	 *The function operation: Closes the server socket and all open threads
	 *********************************************************************/
	void stop();
	
private:
	/********************************************************************
	 *Function name: handleClient()
	 *The input: Struct with necessary arguments
	 *The output: None
	 *The function operation: Creates a new thread for dealing each client's requests.
	 *********************************************************************/
	//static void * handleClient(void * arguments);
	
	/********************************************************************
	 *Function name: receiveMove()
	 *The input: int socket
	 *The output: Pair of ints
	 *The function operation: Receives int twice and returns a pair made of the received values.
	 *********************************************************************/
	pair<int,int> receiveMove(int socket);
	
	/********************************************************************
	 *Function name: passMove()
	 *The input: A pair of ints, target's socket info
	 *The output: None
	 *The function operation: Uses the socket info to send the pair through 2 messages.
	 *********************************************************************/
	void passMove(pair<int,int> move, int socket);
	
	/********************************************************************
	 *Function name: alertClient()
	 *The input: int socket (the target player's socket number)
	 *The output: void
	 *The function operation: Informs the target player that the other player disconnected, through
	 *a defined message
	 *********************************************************************/
	void alertClient(int socket);


	//Members
	int port;
	int serverSocket; // the socket's file descriptor
	bool serverOn;
	CommandsManager *commandsManager;
	pthread_t serverThreadId;
	
};
#endif /* INCLUDE_SERVER_H_ */
