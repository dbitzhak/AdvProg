#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
	GameCenter gc;
	CommandsManager cm(&gc);
	Server server(8008, &cm);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
	return 0;
}
