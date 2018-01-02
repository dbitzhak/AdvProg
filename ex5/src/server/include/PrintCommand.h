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
	PrintCommand();
	virtual void execute(vector<string> args);
};

#endif /* PrintCommand_h */
