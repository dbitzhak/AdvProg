//
//  SerializationTest.hpp
//  Reversi
//
//  Created by Gavriella on 12/7/17.
//  Copyright © 2017 Gavriella. All rights reserved.
//

#ifndef SerializationTest_h
#define SerializationTest_h

#include "gtest/gtest.h"
#include "Serialization.h"
#include "StandardLogic.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"
#include "Player.h"


using namespace std;

class SerializationTest: public testing::Test {
public:
	SerializationTest() {
		ConsoleGraphics *cg = new ConsoleGraphics();
		gi = (GraphicInterface*) cg;
		standardLogic = new StandardLogic(gi);
		GameLogic *gl = (GameLogic*) standardLogic;
		p1 = new HumanPlayer(gi,'O');
		p2 = new MachinePlayer(gl,gi,'X');
 }
	
~SerializationTest() {
	delete standardLogic;
	delete gi;
	delete p1;
	delete p2;
}

protected:
	StandardLogic *standardLogic;
	GraphicInterface* gi;
	HumanPlayer *p1;
	MachinePlayer *p2;
};

#endif /* SerializationTest_h */
