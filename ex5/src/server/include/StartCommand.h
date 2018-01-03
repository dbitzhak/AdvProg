#ifndef StartCommand_h
#define StartCommand_h
#include "Command.h"
#include <iostream>
#include <list>
#include "GameCenter.h"

class StartCommand: public Command {
public:
	StartCommand(GameCenter *gc);
	virtual void execute(vector<string> args, long dstSocket);

private:
	GameCenter *gameCenter;
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* StartCommand_h */
