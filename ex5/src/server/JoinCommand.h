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
	JoinCommand(GameCentral *central);
	
	virtual void execute(vector<string> args) {
		if(!central->isInWaitingList(args[0])) {
			throw "Could not join game";
		}
		//else join...
		central->removeFromWaitingList(args[0]);
	}
private:
	GameCentral *central;
};

#endif /* JoinCommand_h */
