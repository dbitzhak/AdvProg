#ifndef JoinCommand_h
#define JoinCommand_h
#include "Command.h"
#include <iostream>
#include "GameCenter.h"

class JoinCommand: public Command {
public:
	/********************************************************************
	 *Function name: JoinCommand()
	 *The input: pointer to an existing GameCenter object
	 *The output: JoinCommand object
	 *The function operation: Constructor
	 *********************************************************************/
	JoinCommand(GameCenter*gc);

	/********************************************************************
	 *Function name: execute()
	 *The input: args - the necessary parameters as a vector<string> , dstSocket - the socket address that request the command
	 *The output: None
	 *The function operation: Uses GameCenter to connect the dstSocket
	 * to the socket of the game creator and to initialize the match.
	 *********************************************************************/
	virtual void execute(vector<string> args, long dstSocket);
	
	//Members
	pthread_mutex_t lock;
private:
	GameCenter *gameCenter;
	
};

#endif /* JoinCommand_h */
