/*
 * HumanPLayerTest.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: dan
 */

#include "gtest/gtest.h"
#include "HumanPlayerTest.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include <utility>

using namespace std;

TEST_F(HumanPlayerTest, ReturnCorrectIDChar) {

	ConsoleGraphics cg;
	GraphicInterface *gi = (GraphicInterface*) &cg;
	char x = 'X';
	HumanPlayer p1(gi,x);
	Player *hp = (Player*) &p1;
	ASSERT_EQ(hp->getPlayerIdChar(), x);
}





