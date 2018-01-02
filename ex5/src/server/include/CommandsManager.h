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
#include "GameCenter.h"

class CommandsManager {
public:
	CommandsManager(GameCenter *gm);
	~CommandsManager();
	void * executeCommand(string command, vector<string> args, int socket);
private:
	map<string, Command *> commandsMap;
	GameCenter *gameCenter;
};

#endif /* CommandsManager_h */
