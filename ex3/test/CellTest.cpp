/*
 * CellTest.cpp
 *
 *  Created on: Nov 29, 2017
 *      Author: dan
 */



#include "Cell.h"
#include "gtest/gtest.h"

//Tests coordinates
TEST(CellTest, ReturnsCorrectCoordinatesAndSymbol) {
	int x = 10;
	int y = 5;
	char symbol = 'U';
	Cell c(x,y, symbol);
	ASSERT_EQ(x,c.getXCord());
	ASSERT_EQ(y,c.getYCord());
	ASSERT_EQ(symbol,c.getValue());
}

//Tests isSameValue
TEST(CellTest, CorrectIsSameValue) {
	int x = 10;
	int y = 5;
	char symbol = 'U';
	Cell c(x,y, symbol);
	ASSERT_NE(c.isSameValue('X'), true);
	ASSERT_EQ(c.isSameValue('U'), true);
}

//Tests sameCoord
TEST(CellTest, CorrectSameCoord) {
	int x = 10;
	int y = 5;
	char symbol = 'U';
	Cell a(x,y, 'P');
	Cell b(x,y, symbol);
	Cell c(x-1, y+2, symbol);
	ASSERT_NE(b.sameCoord(c), true);
	ASSERT_EQ(a.sameCoord(a), true);
}

//Tests < > and == for Cells
TEST(CellTest, EqualMinorOperatorsWorking) {
	int x = 10;
	int y = 5;
	char symbol = 'U';
	Cell a(x,y-1, 'P');
	Cell b(x,y-1, symbol);
	Cell c(x-1, y, symbol);
	//B is bigger than c
	ASSERT_EQ(b<c, false);
	//Not smaller
	ASSERT_EQ(b<b, false);
	//Different
	ASSERT_EQ(a==c, false);
	//Equal
	ASSERT_EQ(a==b, true);
}
