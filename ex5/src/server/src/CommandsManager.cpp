#include "CommandsManager.h"
#include "StartCommand.h"
#include "JoinCommand.h"
#include "CloseCommand.h"
#include "GameCenter.h"


CommandsManager::CommandsManager(GameCenter *gc) : gameCenter(gc) {
	commandsMap["start"] = new StartCommand(gameCenter);
	commandsMap["join"] = new JoinCommand(gameCenter);
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
		} catch(int e) {
			if(e == TRY_AGAIN) {
				error = true;
			} else {
				return NULL;
			}
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




