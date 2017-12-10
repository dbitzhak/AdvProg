/*
 * test_board.cpp
 *
 *  Created on: Nov 26, 2017
 *      Author: dan
 */

#ifndef TEST_BOARDTEST_H_
#define TEST_BOARDTEST_H_

#include "gtest/gtest.h"
#include "Board.h"

using namespace std;

class BoardTest: public testing::Test {
public:
 BoardTest(): myBoard(8,8) {}

protected:
 Board myBoard;
};

#endif
/* TEST_BOARDTEST_H_ */
