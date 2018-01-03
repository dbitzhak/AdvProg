#ifndef PlayCommand_h
#define PlayCommand_h
#include "Command.h"
#include <iostream>
#include "GameCenter.h"
#include <utility>

class PlayCommand: public Command {
public:
	PlayCommand();
	virtual void execute(vector<string> args, long dstSocket);
private:
	pair<int, int> getMove(string buffer);
	void writeMove(pair<int, int> move, long dstSocket);
};

#endif /* PlayCommand_h */
