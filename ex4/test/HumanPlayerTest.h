/*
 * HumanPlayerTest.h
 *
 *  Created on: Nov 26, 2017
 *      Author: dan
 */



#ifndef TEST_HUMANPLAYERTEST_H_
#define TEST_HUMANPLAYERTEST_H_

#include "gtest/gtest.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"


class HumanPlayerTest: public testing::Test {
public:
 HumanPlayerTest() {
	 ConsoleGraphics cg;
	 	GraphicInterface *gi = (GraphicInterface*) &cg;
	 	HumanPlayer p1(gi,'X');
	 	humanPlayer = (Player*) &p1;
 }

protected:
 Player *humanPlayer;
};

#endif /* TEST_HUMANPLAYERTEST_H_ */
