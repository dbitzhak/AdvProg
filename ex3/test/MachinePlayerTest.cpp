/*
 * MachinePlayerTest.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: dan
 */

#include "MachinePlayerTest.h"
#include "gtest/gtest.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "StandardLogic.h"
#include "GameLogic.h"
#include "Cell.h"
#include <utility>
#include <vector>

using namespace std;

TEST_F(MachinePlayerTest, ReturnCorrectIDChar) {
	ConsoleGraphics cg;
	GraphicInterface *gi = (GraphicInterface*) &cg;
	StandardLogic sl(gi);
	GameLogic *gl = (GameLogic*) &sl;
	char x = 'U';
	MachinePlayer p1(gl,gi,x);
	Player *mp = (Player*) &p1;
	ASSERT_EQ(mp->getPlayerIdChar(), x);
}

TEST_F(MachinePlayerTest, CorrectMakeMove) {
	ConsoleGraphics cg;
	GraphicInterface *gi = (GraphicInterface*) &cg;
	StandardLogic sl(gi);
	GameLogic *gl = (GameLogic*) &sl;
	MachinePlayer p1(gl,gi,'X');
	Player *mp1 = (Player*) &p1;
	MachinePlayer p2(gl,gi,'O');
	Player *mp2 = (Player*) &p2;
	sl.startGame(mp1, mp2);
	vector<Cell> moves(sl.getValidPositions(mp1, sl.getBoard()));
	pair<int,int> validMove = mp1->makeMove();
	Cell c(validMove.first, validMove.second, mp1->getPlayerIdChar());
	bool isValid = false;
	for (unsigned int i = 0; i < moves.size(); i++) {
		if (c == moves.at(i)) {
			isValid = true;
			break;
		}
	}
	ASSERT_EQ(isValid, true);
}




