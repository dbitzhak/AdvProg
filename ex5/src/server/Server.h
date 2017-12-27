#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#define ERROR -5
#define END -666

#include <utility>
using namespace std;

//Server class
class Server {
public:
	/********************************************************************
	 *Function name: Server()
	 *The input: int representing the port number
	 *The output: Server object
	 *The function operation: Constructor
	 *********************************************************************/
	Server(int port);
	
	/********************************************************************
	 *Function name: start()
	 *The input: None
	 *The output: None
	 *The function operation: Starts listening for input through a socket
	 * and waits for 2 players to connect.
	 *********************************************************************/
	void start();
	
	/********************************************************************
	 *Function name: stop()
	 *The input: None
	 *The output: None
	 *The function operation: Closes the server socket
	 *********************************************************************/
	void stop();
	
private:
	/********************************************************************
	 *Function name: handleClients()
	 *The input: int socket of the first player, int socket of the second player.
	 *The output: None
	 *The function operation: Sends them a message with their respective order and then keeps
	 * transmitting messages (moves) between them until told otherwise by an encoded message.
	 *********************************************************************/
	void handleClients(int clientSocket1, int clientSocket2);
	
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
	 *The function operation: Uses thr socket info to send the pair through 2 messages.
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
	
};
#endif /* INCLUDE_SERVER_H_ */
