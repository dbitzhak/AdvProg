//
//  CommandManager.c
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#include "CommandsManager.h"
#include "PrintCommand.h"
#include "StartCommand.h"
#include "ListGames.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"

CommandsManager::CommandsManager() {
	commandsMap["print"] = new PrintCommand();
	commandsMap["start"] = new StartCommand();
	commandsMap["list_games"] = new ListGamesCommand();
	commandsMap["join"] = new JoinCommand();
	commandsMap["play"] = new PlayCommand();
	commandsMap["close"] = new CloseCommand();
}

void CommandsManager::executeCommand(string command, vector<string> args) {
	Command *commandObj = commandsMap[command];
	commandObj->execute(args);
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}




