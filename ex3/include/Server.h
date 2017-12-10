/*
 * Server.h
 *
 *  Created on: Dec 3, 2017
 *      Author: dan
 */

#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include "Board.h"

class Server {
public:
 Server(int port);
 void start();
 void stop();
private:
 int port;
 int serverSocket; // the socket's file descriptor
 void handleClients(int clientSocket1, int clientSocket2);
 void handleClient(int clientSocket);
 int calc(int arg1, const char op, int arg2) const;
};

#endif /* INCLUDE_SERVER_H_ */
