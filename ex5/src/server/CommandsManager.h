//
//  CommandManager.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef CommandsManager_h
#define CommandsManager_h

#include <map>
#include "Command.h"
#include "GameInfo.h"

class CommandsManager {
public:
	CommandsManager();
	~CommandsManager();
	void executeCommand(string command, vector<string> args);
private:
	map<string, Command *> commandsMap;
	GameInfo *gameInfo;
};

#endif /* CommandsManager_h */
