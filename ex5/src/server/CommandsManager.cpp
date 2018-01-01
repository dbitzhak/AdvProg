//
//  CommandManager.c
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#include <ListGamesCommand.h>
#include "CommandsManager.h"
#include "PrintCommand.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"
#include "GameCenter.h"


CommandsManager::CommandsManager(GameCenter *gc) : gameCenter(gc) {
	commandsMap["print"] = new PrintCommand();
	commandsMap["start"] = new StartCommand(gameCenter);
	commandsMap["list_games"] = new ListGamesCommand(gameCenter);
	commandsMap["join"] = new JoinCommand(gameCenter);
	commandsMap["play"] = new PlayCommand();
	commandsMap["close"] = new CloseCommand(gameCenter);
}

void * CommandsManager::getUserCommand(int clientSocket) {
	return NULL;
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}




