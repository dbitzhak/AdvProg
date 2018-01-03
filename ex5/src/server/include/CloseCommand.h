#ifndef CloseCommand_h
#define CloseCommand_h
#include "Command.h"
#include <iostream>
#include "GameCenter.h"

class CloseCommand: public Command {
public:
	CloseCommand(GameCenter *gc);
	virtual void execute(vector<string> args, long dstSocket);
	
private:
	GameCenter *gameCenter;
};

#endif /* CloseCommand_h */
