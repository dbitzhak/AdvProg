#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#include "Server.h"
#include "GameCenter.h"

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
	 string input;
	    getline(cin,input);
		// your code goes here
	cout << input;

	int port;
	try {
		port = getPort("serverconfig.txt");
	} catch(const char *msg) {
		cout << msg << endl;
		exit(-1);
	}
	GameCenter gc;
	CommandsManager cm(&gc);
	Server server(port, &cm);
	//	Server server(8000);
	try {
		server.start();
	} catch(const char *msg) {
		cout << "Cannot start server. Reason: " << msg << endl;
		exit(-1);
	}
}
