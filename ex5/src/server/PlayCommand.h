//
//  PlayCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef PlayCommand_h
#define PlayCommand_h
#include "Command.h"
#include <iostream>
#include "GameCenter.h"

class PlayCommand: public Command {
public:
	virtual void execute(vector<string> args) {
		for(unsigned int i = 0; i < args.size(); i++) {
			cout << args[i] << " ";
		}
		cout << endl;
	}
};

#endif /* PlayCommand_h */
