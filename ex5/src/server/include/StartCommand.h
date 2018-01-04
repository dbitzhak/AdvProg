#ifndef StartCommand_h
#define StartCommand_h
#include "Command.h"
#include <iostream>
#include <list>
#include "GameCenter.h"

class StartCommand: public Command {
public:
	/********************************************************************
	 *Function name: StartCommand()
	 *The input: pointer to an existing GameCenter object
	 *The output: StartCommand object
	 *The function operation: Constructor
	 *********************************************************************/
	StartCommand(GameCenter *gc);

	/********************************************************************
	 *Function name: execute()
	 *The input: args - the necessary parameters as a vector<string> , dstSocket - the socket address that request the command
	 *The output: None
	 *The function operation: Uses GameCenter to create a game associated to the dstSocket
	 *********************************************************************/
	virtual void execute(vector<string> args, long dstSocket);

private:
	GameCenter *gameCenter;
	vector<string> gameList;
	vector<string> waitingList;
};

#endif /* StartCommand_h */
