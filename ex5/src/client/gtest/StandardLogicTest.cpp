#include "gtest/gtest.h"
#include "StandardLogic.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "StandardLogicTest.h"
#include "Board.h"
#include "GameLogic.h"
#include "Cell.h"
#include <vector>
#include "Player.h"


TEST_F(StandardLogicTest, StartsBoardProperly) {
	//Starts the Game
	Player *mp1 = (Player*) p1;
	Player *mp2 = (Player*) p2;
	standardLogic->startGame(mp1, mp2);
	ConsoleGraphics cg;
	//Check if the board was filled correctly
	Board dummyBoard(*(standardLogic->getBoard()));
	for (int i = 0; i < dummyBoard.getNumRows(); i++) {
			for (int j = 0; j < dummyBoard.getNumCol(); j++) {
				if ((i == 3 && j == 4) || (i == 4 && j == 3)) {
					ASSERT_EQ(dummyBoard.getCellValue(i,j), 'O');
				} else if ((i == 3 && j == 3) || (i == 4 && j == 4)) {
					ASSERT_EQ(dummyBoard.getCellValue(i,j), 'X');
				} else {
					ASSERT_EQ(dummyBoard.getCellValue(i,j), ' ');
				}
			}
	}
	standardLogic->endGame();
}
TEST_F(StandardLogicTest, GameEndsCorrectly) {
		//Starts the Board
		Player *mp1 = p1;
		Player *mp2 = p2;
		standardLogic->startGame(mp1,mp2);
		// 1 -  Test Check if gameEnded returns false value when there are plays left.
		ASSERT_EQ(standardLogic->gameEnded(), false);
		//2 - See if when gameEnded becomes true no plays are possible
		vector<Cell> mp1moves;
		vector<Cell> mp2moves;
		//Plays until gameEnded becomes true
		//Asserts there are plays left;
		while(!standardLogic->gameEnded()) {
			mp1moves = standardLogic->getValidPositions(mp1, standardLogic->getBoard());
			mp2moves = standardLogic->getValidPositions(mp2, standardLogic->getBoard());
			ASSERT_EQ(mp1moves.empty() && mp2moves.empty(), false);
			standardLogic->playNextTurn();
		 }
		//Checks if no remaining plays are possible
		mp1moves = standardLogic->getValidPositions(mp1, standardLogic->getBoard());
		mp2moves = standardLogic->getValidPositions(mp2, standardLogic->getBoard());
		ASSERT_EQ(mp1moves.empty() && mp2moves.empty(), true);
		standardLogic->endGame(); //frees memory
}
TEST_F(StandardLogicTest, GetCorrectWinner) {
	//Starts the Board
	Player *mp1 = p1;
	Player *mp2 = p2;
	standardLogic->startGame(mp1,mp2);
	while(!standardLogic->gameEnded()) {
				standardLogic->playNextTurn();
	}
	int counterP1 = 0;
	int counterP2 = 0;
	Board dummyBoard(*(standardLogic->getBoard()));
		for (int i = 0; i < dummyBoard.getNumRows(); i++) {
				for (int j = 0; j < dummyBoard.getNumCol(); j++) {
					if (dummyBoard.getCellValue(i,j) == p1->getPlayerIdChar()) {
						counterP1++;
					} else if(dummyBoard.getCellValue(i,j) == p2->getPlayerIdChar()) {
						counterP2++;
					}
				}
		}
	Player *winner;
	winner = standardLogic->getWinner();
	if(counterP2 > counterP1) {
		EXPECT_EQ(p2->getPlayerIdChar() == winner->getPlayerIdChar(),true);
	} else if(counterP2 < counterP1) {
		EXPECT_EQ(p1->getPlayerIdChar() == winner->getPlayerIdChar(),true);
	} else {
		EXPECT_EQ(winner == 0,true);
	}
	standardLogic->endGame();
}

TEST_F(StandardLogicTest, ValidPositionsAreCorrect) {
	//Starts the Board
	Player *mp1 = p1;
	Player *mp2 = p2;
	standardLogic->startGame(mp1,mp2);
	vector<Cell> positionsP1 = standardLogic->getValidPositions(mp1,standardLogic->getBoard());
	vector<Cell> positionsP2 = standardLogic->getValidPositions(mp2,standardLogic->getBoard());

	EXPECT_EQ((positionsP1[0].getXCord() == 2) && (positionsP1[0].getYCord() == 3), true);
	EXPECT_EQ((positionsP1[1].getXCord() == 3) && (positionsP1[1].getYCord() == 2), true);
	EXPECT_EQ((positionsP1[2].getXCord() == 4) && (positionsP1[2].getYCord() == 5), true);
	EXPECT_EQ((positionsP1[3].getXCord() == 5) && (positionsP1[3].getYCord() == 4), true);
	///For player2 now
	EXPECT_EQ((positionsP2[0].getXCord() == 2) && (positionsP2[0].getYCord() == 4), true);
	EXPECT_EQ((positionsP2[1].getXCord() == 3) && (positionsP2[1].getYCord() == 5), true);
	EXPECT_EQ((positionsP2[2].getXCord() == 4) && (positionsP2[2].getYCord() == 2), true);
	EXPECT_EQ((positionsP2[3].getXCord() == 5) && (positionsP2[3].getYCord() == 3), true);
	standardLogic->endGame();
	}
