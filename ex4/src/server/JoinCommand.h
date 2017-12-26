//
//  JoinCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef JoinCommand_h
#define JoinCommand_h
#include "Command.h"
#include <iostream>

class JoinCommand: public Command {
public:
	virtual void execute(vector<string> args) {
		for(int i = 0; i < args.size(); i++) {
			cout << args[i] << " ";
		}
		cout << endl;
	}
};

#endif /* JoinCommand_h */
