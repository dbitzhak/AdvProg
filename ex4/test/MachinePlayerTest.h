#ifndef TEST_MACHINEPLAYERTEST_H_
#define TEST_MACHINEPLAYERTEST_H_

#include "gtest/gtest.h"
#include "Player.h"
#include "MachinePlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "StandardLogic.h"
#include "GameLogic.h"

class MachinePlayerTest: public testing::Test {

public:
 MachinePlayerTest() {
	 ConsoleGraphics cg;
	 GraphicInterface *gi = (GraphicInterface*) &cg;
	 StandardLogic sl(gi);
	 GameLogic *gl = (GameLogic*) &sl;
	 MachinePlayer p2(gl,gi,'Y');
	 machinePlayer = (Player*) &p2;
 }

protected:
 Player *machinePlayer;
};

#endif /* TEST_MACHINEPLAYERTEST_H_ */
