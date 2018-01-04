#include "Server.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int getPort() {
	ifstream infile;
	
	infile.open("serverconfig.txt");
	if (!infile) {
		cout << "Error opening file\n";
	}
	
	char buffer[20], port[5];
	infile >> buffer >> port;
	port[4] = '\0';
	infile.close();
	
	stringstream s(port);
	int p = 0;
	s >> p;
	return p;
}

int main() {

	ifstream infile;
	
	infile.open("serverconfig.txt");
	if (!infile) {
		cout << "Error opening file\n";
	}
	
	char buffer[20], port[5];
	infile >> buffer >> port;
	port[4] = '\0';
	infile.close();
	
	stringstream s(port);
	int p = 0;
	s >> p;
	GameCenter gc;
	CommandsManager cm(&gc);
	Server server(p, &cm);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
	return 0;
}
