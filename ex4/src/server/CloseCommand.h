//
//  CloseCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef CloseCommand_h
#define CloseCommand_h
#include "Command.h"
#include "GameInfo.h"
#include <iostream>

class CloseCommand: public Command {
public:
	CloseCommand(GameInfo *gameInfo);
	
	virtual void execute(vector<string> args) {
		gameInfo->removeFromGameList(args[0]);
		//close...
	}
	
private:
	GameInfo *gameInfo;
};

#endif /* CloseCommand_h */
