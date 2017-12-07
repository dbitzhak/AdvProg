/*
 * Serialization.h
 *
 *  Created on: Dec 6, 2017
 *      Author: dan
 */

#ifndef INCLUDE_SERIALIZATION_H_
#define INCLUDE_SERIALIZATION_H_

#include "Cell.h"
#include "Board.h"
#include "HumanPlayer.h"
#include "Player.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"

#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost\serialization\export.hpp>

void serializePlayer(const HumanPlayer &player, const char *fileName);
HumanPlayer deserializePlayer(const char *fileName);
void serializeBoard(const Board &b, const char *fileName);
Board deserializeBoard(const char *fileName);
void serializeCell(const Cell &c, const char *fileName);
Cell deserializeCell(const char *fileName);
void serializeConsoleGraphics(const ConsoleGraphics &cg, const char *fileName);
ConsoleGraphics deserializeConsoleGraphics(const char *fileName);



#endif /* INCLUDE_SERIALIZATION_H_ */
