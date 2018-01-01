/*
 * PrintCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */

#include "PrintCommand.h"

PrintCommand::PrintCommand() {}

void PrintCommand::execute(vector<string> args) {
	for(unsigned int i = 0; i < args.size(); i++) {
			cout << args[i] << " ";
	}
		cout << endl;
}

