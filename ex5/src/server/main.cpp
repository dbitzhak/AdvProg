#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int getPort(const char* file) {
	ifstream infile;
	
	infile.open(file);
	if (!infile) {
		cout << "error opening file";
	}
	
	char port[5];
	infile >> port;
	port[4] = '\0';
	infile.close();
	
	stringstream s(port);
	int p = 0;
	s >> p;
	return p;
}

int main() {
	Server server(getPort("serverconfig.txt"));
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
