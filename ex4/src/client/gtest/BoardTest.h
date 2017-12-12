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
