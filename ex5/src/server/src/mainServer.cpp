#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main_Server() {
	GameCenter gc;
	CommandsManager cm(&gc);
	Server server(8000, &cm);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
	return 0;
}
