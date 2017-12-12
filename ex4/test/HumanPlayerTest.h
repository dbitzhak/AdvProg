#ifndef TEST_HUMANPLAYERTEST_H_
#define TEST_HUMANPLAYERTEST_H_

#include "gtest/gtest.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "StandardLogic.h"


class HumanPlayerTest: public testing::Test {
public:
 HumanPlayerTest() {
		ConsoleGraphics cg;
		GraphicInterface *gi = (GraphicInterface*) &cg;
		StandardLogic sl(gi);
		GameLogic *gl = &sl;
		HumanPlayer p1(gl, gi,'X');
		humanPlayer = (Player*) &p1;
 }

protected:
 Player *humanPlayer;
	GameLogic *gl;
};

#endif /* TEST_HUMANPLAYERTEST_H_ */
