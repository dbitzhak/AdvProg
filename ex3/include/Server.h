/*
 * Server.h
 *
 *  Created on: Dec 3, 2017
 *      Author: dan
 */

#ifndef INCLUDE_SERVER_H_
#define INCLUDE_SERVER_H_

#include "Serialization.h"
#include "Board.h"

class Server {
public:
 Server(int port);
 void start();
 void stop();
private:
 int port;
 int serverSocket; // the socket's file descriptor
 void handleClient(int clientSocket);
 int calc(int arg1, const char op, int arg2) const;
 Serialization serialize; //Used for serialization and deserialization

};

#endif /* INCLUDE_SERVER_H_ */
