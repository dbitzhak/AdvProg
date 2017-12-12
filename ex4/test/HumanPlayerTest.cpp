#include "gtest/gtest.h"
#include "HumanPlayerTest.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "StandardLogic.h"
#include <utility>

using namespace std;

TEST_F(HumanPlayerTest, ReturnCorrectIDChar) {

	ConsoleGraphics cg;
	GraphicInterface *gi = (GraphicInterface*) &cg;
	StandardLogic sl(gi);
	GameLogic *gl = &sl;
	char x = 'X';
	HumanPlayer p1(gl, gi,x);
	Player *hp = (Player*) &p1;
	ASSERT_EQ(hp->getPlayerIdChar(), x);
}





