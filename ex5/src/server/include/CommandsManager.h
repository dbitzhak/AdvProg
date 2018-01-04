#ifndef CommandsManager_h
#define CommandsManager_h

#include <map>
#include "Command.h"
#include "GameCenter.h"

class CommandsManager {
public:
	/********************************************************************
	 *Function name: CommandsManager()
	 *The input: pointer to an existing GameCenter object
	 *The output: CommandsManager object
	 *The function operation: Constructor
	 *********************************************************************/
	CommandsManager(GameCenter *gm);

	/********************************************************************
	 *Function name: ~CommandsManager()
	 *The input: None
	 *The output: None
	 *The function operation: Destructor
	 *********************************************************************/
	~CommandsManager();

	/********************************************************************
	 *Function name: executeCommand()
	 *The input: string command, args - vector<string> the list of command args,
	 * socket - the socket address that requested the command
	 *The output: None
	 *The function operation: Looks in the map for the equivalent Command object and executes it with the given args
	 *********************************************************************/
	void * executeCommand(string command, vector<string> args, int socket);

private:
	//Members
	map<string, Command *> commandsMap;
	GameCenter *gameCenter;
};

#endif /* CommandsManager_h */
