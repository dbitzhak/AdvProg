#ifndef ListGamesCommand_h
#define ListGamesCommand_h
#include "Command.h"
#include <iostream>
#include <list>
#include "GameCenter.h"

class ListGamesCommand: public Command {
public:
	ListGamesCommand(GameCenter *gc);
	
	virtual void execute(vector<string> args, long dstSocket);
	

	//return a list of games that the player can join (that only one player is currently in)
	virtual list<string> listGames();

	void removeFromWaitingList(string name);
private:
	GameCenter *gameCenter;
	vector<string> gameList;
	list<string> waitingList;
};

#endif /* ListGamesCommand_h */
