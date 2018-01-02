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
#include "GameCenter.h"

class JoinCommand: public Command {
public:
	JoinCommand(GameCenter*gc);
	virtual void execute(vector<string> args);
private:
	GameCenter *gameCenter;
};

#endif /* JoinCommand_h */
