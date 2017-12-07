//
//  SerializationTest.cpp
//  Reversi
//
//  Created by Gavriella on 12/7/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#include "SerializationTest.h"


TEST_F(SerializationTest, SerializesBoard) {
	//Starts the Game
	Player *mp1 = (Player*) p1;
	Player *mp2 = (Player*) p2;
	standardLogic->startGame(mp1, mp2);
	ConsoleGraphics cg;
	//Check if the board was filled correctly
	Board dummyBoard(*(standardLogic->getBoard()));
	
	const char *boardFile;
	serializeBoard(dummyBoard, boardFile);
	Board deserializedBoard = deserializeBoard(boardFile);
	
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
