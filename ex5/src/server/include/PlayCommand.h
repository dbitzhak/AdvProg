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
	PlayCommand();
	virtual void execute(vector<string> args);
};

#endif /* PlayCommand_h */
