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
#include "GameInfo.h"
#include <iostream>
#include <list>

class StartCommand: public Command {
public:
	StartCommand(GameInfo *gameInfo);
	virtual void execute(vector<string> args) {
		if(gameInfo->isInGameList(args[0])) {
			throw "Could not add name to game list";
		}
		gameInfo->addToWaitingList(args[0]);
		gameInfo->addToGameList(args[0]);
	}

private:
	GameInfo *gameInfo;
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* StartCommand_h */
