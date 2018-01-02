//
//  Command.h
//  Server
//
//  Created by Gavriella on 12/26/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef Command_h
#define Command_h

#include <vector>
#include <string>

using namespace std;

class Command {
public:
	virtual void execute(vector<string> args, long dstSocket) = 0;
	virtual ~Command() {}
};


#endif /* Command_h */
