#include <iostream>
#include "ConsoleGraphics.h"
#include "GraphicInterface.h"
#include "Game.h"

using namespace std;


/******************************************************
 *Function name: main()
 *The output: 0 if successful other numbers if not.
 ********************************************************/
int main() {
	ConsoleGraphics cg;
	GraphicInterface *gi = &cg;
	Game myGame(gi);
	myGame.start();
	return 0;
}
