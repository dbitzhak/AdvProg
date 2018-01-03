#include "ListGamesCommand.h"
#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "PlayCommand.h"
#include "CloseCommand.h"
#include "GameCenter.h"


CommandsManager::CommandsManager(GameCenter *gc) : gameCenter(gc) {
	commandsMap["start"] = new StartCommand(gameCenter);
	commandsMap["list_games"] = new ListGamesCommand(gameCenter);
	commandsMap["join"] = new JoinCommand(gameCenter);
	commandsMap["play"] = new PlayCommand();
	commandsMap["close"] = new CloseCommand(gameCenter);
}

void * CommandsManager::executeCommand(string command, vector<string> args, int socket) {
	cout << command << endl;
	Command *commandObj = commandsMap[command];
	bool error = true;
	while(error) {
		error = false;
		try {
			commandObj->execute(args, socket);
		} catch(const char *msg) {
			cout << msg << endl;
			error = true;
		}
	}
	return NULL;
}

CommandsManager::~CommandsManager() {
	map<string, Command *>::iterator it;
	for(it = commandsMap.begin(); it != commandsMap.end(); it++) {
		delete it->second;
	}
}




