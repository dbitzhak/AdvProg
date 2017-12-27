//
//  PrintCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef PrintCommand_h
#define PrintCommand_h
#include "Command.h"
#include <iostream>

class PrintCommand: public Command {
public:
	virtual void execute(vector<string> args) {
		for(unsigned int i = 0; i < args.size(); i++) {
			cout << args[i] << " ";
		}
		cout << endl;
	}
};

#endif /* PrintCommand_h */
