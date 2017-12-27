#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

int getPort(const char* file) {
	ifstream infile;
	
	infile.open(file);
	if (!infile) {
		throw "Error opening file";
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
	int port;
	try {
		port = getPort("serverconfig.txt");
	} catch(const char *msg) {
		cout << msg << endl;
		exit(-1);
	}
	Server server(port);
	//	Server server(8000);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
