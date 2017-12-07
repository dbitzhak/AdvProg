/*
 * test_board.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: dan
 */



#include "BoardTest.h"
#include "gtest/gtest.h"

using namespace std;

//Tests that each cell is initiated as empty, ' '
TEST_F(BoardTest, BoardStartsWithEmptyCells) {
	int columns = 8;
	int rows = 6;
	Board b(rows,columns);
	for (int i = 0; i < b.getNumRows(); i++) {
		for (int j = 0; j < b.getNumRows(); j++) {
			ASSERT_EQ(b.getCellValue(i,j), ' ');
		}
	}
}

//Tests that getCellValue returns cell value
TEST_F(BoardTest, InsertionRetrievalOfValues) {
	int row = myBoard.getNumRows()/2;
	int col = myBoard.getNumCol()/2;
	myBoard.setCell(row,col,'Z');
	ASSERT_EQ(myBoard.getCellValue(row,col), 'Z');
}

//Tests getXCord and getYCord methods
TEST_F(BoardTest, CoordinatesAreCorrect) {
	int row = myBoard.getNumRows()/2 - 1;
	int col = myBoard.getNumCol()/2 + 1;
	Cell *c = myBoard.getCell(row,col);
	ASSERT_EQ(c->getXCord(), row);
	ASSERT_EQ(c->getYCord(), col);
}

//Tests the copy constructor
TEST_F(BoardTest, CopyConstructorWorks) {
	for (int i = 0; i < myBoard.getNumRows(); i++) {
			for (int j = 0; j < myBoard.getNumRows(); j++) {
				myBoard.setCell(i,j,'A' + 1);
			}
		}
	Board copyBoard(myBoard);
	for (int i = 0; i < myBoard.getNumRows(); i++) {
				for (int j = 0; j < myBoard.getNumRows(); j++) {
					ASSERT_EQ(myBoard.getCellValue(i,j), copyBoard.getCellValue(i,j));
					ASSERT_NE(myBoard.getCell(i,j), copyBoard.getCell(i,j));
				}
			}
}
