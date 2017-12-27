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
#include "GameInfo.h"
#include <iostream>

class JoinCommand: public Command {
public:
	JoinCommand(GameInfo *gameInfo);
	
	virtual void execute(vector<string> args) {
		if(!gameInfo->isInWaitingList(args[0])) {
			throw "Could not join game";
		}
		//else join...
		gameInfo->removeFromWaitingList(args[0]);
	}
private:
	GameInfo *gameInfo;
};

#endif /* JoinCommand_h */
