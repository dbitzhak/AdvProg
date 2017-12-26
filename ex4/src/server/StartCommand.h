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

class StartCommand: public Command {
public:
	virtual void execute(vector<string> args) {
		for(int i = 0; i < gameList.size(); i++) {
			if(gameList[i] == args[0]) {
				
			}
		}
		gameList.push_back(args[0]);
		waitingList.push_back(args[0]);
	}

	
	//return a list of games that the player can join (that only one player is currently in)
	virtual list<string> listGames() {
		return waitingList;
	}
	
	void removeFromWaitingList(string name) {
		try {
			waitingList.remove(name);
		} catch(exception e) {
			throw "Could not remove name from waiting list";
		}
	}
	
private:
	vector<string> gameList;
	list<string> waitingList;
};

#endif /* StartCommand_h */
