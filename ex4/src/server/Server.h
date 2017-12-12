/*
 * Server.h
 *
 *  Created on: Dec 3, 2017
 *      Author: dan
 */

#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#define ERROR -5
#define END -666

#include <utility>
using namespace std;

class Server {
	public:
		Server(int port);
		void start();
		void stop();
	private:
		int port;
		int serverSocket; // the socket's file descriptor
		void handleClients(int clientSocket1, int clientSocket2);
		pair<int,int> receiveMove(int socket);
		void passMove(pair<int,int> move, int socket);
		void alertClient(int socket);
};

#endif /* INCLUDE_SERVER_H_ */
