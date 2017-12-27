//
//  StartCommand.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef ListGamesCommand_h
#define ListGamesCommand_h
#include "Command.h"
#include "GameInfo.h"
#include <iostream>
#include <list>

class ListGamesCommand: public Command {
public:
	ListGamesCommand(GameInfo *gameInfo);
	
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
	GameInfo *gameInfo;
	vector<string> gameList;
	list<string> waitingList;
};

#endif /* ListGamesCommand_h */
