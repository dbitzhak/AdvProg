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
	StartCommand(GameCentral *gameCentral);
	virtual void execute(vector<string> args) {
		if(central->isInGameList(args[0])) {
			throw "Could not add name to game list";
		}
		central->addToWaitingList(args[0]);
		central->addToGameList(args[0]);
	}

private:
	GameCentral *central;
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* StartCommand_h */
