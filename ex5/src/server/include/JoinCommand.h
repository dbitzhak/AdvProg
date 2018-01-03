#ifndef JoinCommand_h
#define JoinCommand_h
#include "Command.h"
#include <iostream>
#include "GameCenter.h"

class JoinCommand: public Command {
public:
	JoinCommand(GameCenter*gc);
	virtual void execute(vector<string> args, long dstSocket);
private:
	GameCenter *gameCenter;
};

#endif /* JoinCommand_h */
