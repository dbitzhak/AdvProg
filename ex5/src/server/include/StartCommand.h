//
//  StartCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef StartCommand_h
#define StartCommand_h
#include "Command.h"
#include <iostream>
#include <list>
#include "GameCenter.h"

class StartCommand: public Command {
public:
	StartCommand(GameCenter *gc);
	virtual void execute(vector<string> args);

private:
	GameCenter *gameCenter;
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* StartCommand_h */
