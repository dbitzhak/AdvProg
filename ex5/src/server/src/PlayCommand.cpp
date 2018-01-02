/*
 * PlayCommand.cpp
 *
 *  Created on: Dec 30, 2017
 *      Author: dan
 */

#include "PlayCommand.h"

PlayCommand::PlayCommand() {}

void PlayCommand::execute(vector<string> args) {
	for(unsigned int i = 0; i < args.size(); i++) {
			cout << args[i] << " ";
		}
		cout << endl;
}
