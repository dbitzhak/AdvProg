/*
 * gtest_main.cpp
 *
 *  Created on: Nov 25, 2017
 *      Author: dan
 */

#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

