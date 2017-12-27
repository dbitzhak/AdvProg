//
//  GameInfo.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef GameCentral_h
#define GameCentral_h
#include <vector>
#include <list>
#include <string>

using namespace std;

class GameCentral {
public:
	vector<string> getWaitingList() {
		return waitingList;
	}
	
	void addToWaitingList(string name) {
		for(unsigned int i = 0; i < waitingList.size(); i++) {
			if(name == waitingList[i]) {
				throw "Could not add name to waiting list";
			}
		}
		waitingList.push_back(name);
	}
	
	void addToGameList(string name) {
		for(unsigned int i = 0; i < gameList.size(); i++) {
			if(name == gameList[i]) {
				throw "Could not add name to game list";
			}
		}
		gameList.push_back(name);
	}
	
	void removeFromWaitingList(string name) {
		for(unsigned int i = 0; i < waitingList.size(); i++) {
			if(name == waitingList[i]) {
				waitingList.erase(waitingList.begin() + i);
				return;
			}
		}
		throw "Could not remove name from waiting list";
	}
	
	void removeFromGameList(string name) {
		for(unsigned int i = 0; i < gameList.size(); i++) {
			if(name == gameList[i]) {
				gameList.erase(gameList.begin() + i);
			}
		}
		throw "Could not remove name from game list";
	}
	
	bool isInGameList(string name) {
		for(unsigned int i = 0; i < gameList.size(); i++) {
			if(name == gameList[i]) {
				return true;
			}
		}
		return false;
	}
	
	bool isInWaitingList(string name) {
		for(unsigned int i = 0; i < waitingList.size(); i++) {
			if(name == waitingList[i]) {
				return true;
			}
		}
		return false;
	}
	
private:
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* GameCentral_h */
