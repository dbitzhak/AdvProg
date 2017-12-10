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
#include<boost/archive/binary_iarchive.hpp>
#include<boost/archive/binary_oarchive.hpp>
#include<boost/serialization/vector.hpp>

BOOST_CLASS_EXPORT(HumanPlayer);

using namespace std;

void Serialization::serializeHumanPlayer(const HumanPlayer& player, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::binary_oarchive outArchive(out);
	 // Write object
	 outArchive & player;
}

HumanPlayer Serialization::deserializeHumanPlayer(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::binary_iarchive inArchive(in);
	 // Load data
	 HumanPlayer hp;
	 inArchive & hp;
	 return hp;
}

void Serialization::serializeBoard(const Board& b, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::binary_oarchive outArchive(out);
	 // Write object
	 outArchive & b;
}

Board Serialization::deserializeBoard(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::binary_iarchive inArchive(in);
	 // Load data
	 Board b;
	 inArchive & b;
	 return b;
}

void Serialization::serializeCell(const Cell& c, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::binary_oarchive outArchive(out);
	 // Write object
	 outArchive & c;

}

Cell Serialization::deserializeCell(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::binary_iarchive inArchive(in);
	 // Load data
	 Cell c;
	 inArchive & c;
	 return c;
}

void Serialization::serializeConsoleGraphics(const ConsoleGraphics& cg, const char* fileName) {
	 // Create an output archive
	 ofstream out(fileName);
	 boost::archive::binary_oarchive outArchive(out);
	 // Write object
	 outArchive & cg;
}

ConsoleGraphics Serialization::deserializeConsoleGraphics(const char* fileName) {
	 // Create an input archive
	 std::ifstream in(fileName);
	 boost::archive::binary_iarchive inArchive(in);
	 // Load data
	 ConsoleGraphics cg;
	 inArchive & cg;
	 return cg;
}

void Serialization::serializeValidMoves(const vector<Cell>& moves, const char* fileName) {
	 // Create an output archive
		 ofstream out(fileName);
		 boost::archive::binary_oarchive outArchive(out);
		 // Write object
		 outArchive & moves;
}

std::vector<Cell> Serialization::deserializeValidMoves(const char* fileName) {
	 // Create an input archive
		 std::ifstream in(fileName);
		 boost::archive::binary_iarchive inArchive(in);
		 // Load data
		 vector<Cell> moves;
		 inArchive & moves;
		 return moves;
}

int Serialization::getBinaryFileSize(const char *filename)
{
    ifstream file(filename, ifstream::in | ifstream::binary);
    if(!file.is_open())
    {
        return -1;
    }
    file.seekg(0, ios::end);
    int fileSize = file.tellg();
    file.close();
    return fileSize;
}
