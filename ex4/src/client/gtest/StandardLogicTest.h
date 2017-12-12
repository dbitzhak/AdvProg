#ifndef TEST_STANDARDLOGICTEST_H_
#define TEST_STANDARDLOGICTEST_H_

#include "gtest/gtest.h"
#include "StandardLogic.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "MachinePlayer.h"
#include "Player.h"

using namespace std;

class StandardLogicTest: public testing::Test {
public:
StandardLogicTest() {
	ConsoleGraphics *cg = new ConsoleGraphics();
	gi = (GraphicInterface*) cg;
	standardLogic = new StandardLogic(gi);
	GameLogic *gl = (GameLogic*) standardLogic;
	p1 = new MachinePlayer(gl,gi,'O');
	p2 = new MachinePlayer(gl,gi,'X');
 }

~StandardLogicTest() {
	delete standardLogic;
	delete p1;
	delete p2;
	delete gi;
 }

protected:
 StandardLogic* standardLogic;
 GraphicInterface* gi;
 MachinePlayer *p1;
 MachinePlayer *p2;
};


#endif /* TEST_STANDARDLOGICTEST_H_ */
