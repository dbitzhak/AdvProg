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
