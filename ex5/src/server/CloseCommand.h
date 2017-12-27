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
#include <iostream>
#include "GameCenter.h"

class CloseCommand: public Command {
public:
	CloseCommand(GameCentral *gameCentral);
	
	virtual void execute(vector<string> args) {
		central->removeFromGameList(args[0]);
		//close...
	}
	
private:
	GameCentral *central;
};

#endif /* CloseCommand_h */
