/*
 * Serialization.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: dan
 */

#include "Cell.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "GraphicInterface.h"
#include "Serialization.h"

#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

BOOST_CLASS_EXPORT(HumanPlayer);

using namespace std;

void serializePlayer(const Player &player, const char *fileName) {
	// Create an output archive
	ofstream out(fileName);
	boost::archive::text_oarchive outArchive(out);
	// Write object
	outArchive & player;
}

void serializePlayer(const HumanPlayer& player, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::text_oarchive outArchive(out);
	 // Write object
	 outArchive & player;
}

HumanPlayer deserializePlayer(const char *fileName) {
 // Create an input archive
 std::ifstream in(fileName);
 boost::archive::text_iarchive inArchive(in);
 // Load object
 HumanPlayer *hp;
 inArchive & hp;
 return *hp;
}

void serializeBoard(const Board& b, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::text_oarchive outArchive(out);
	 // Write object
	 outArchive & b;
}

Board deserializeBoard(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::text_iarchive inArchive(in);
	 // Load object
	 Board b;
	 inArchive & b;
	 return b;
}

void serializeConsoleGraphics(const ConsoleGraphics& cg, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::text_oarchive outArchive(out);
	 // Write object
	 outArchive & cg;
}

ConsoleGraphics deserializeConsoleGraphics(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::text_iarchive inArchive(in);
	 // Load object
	 ConsoleGraphics *cg;
	 inArchive & cg;
	 return *cg;
}
