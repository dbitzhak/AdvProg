/*
 * StandardLogic.cpp
 *  Author: Daniel Ben Itzhak
 *      338017437
 */

#include "StandardLogic.h"
#include "Board.h"
#include "Cell.h"
#include "Player.h"
#include <vector>
#include <map>
#include <iostream>
#include <utility>
#include <algorithm>


using namespace std;


StandardLogic:: StandardLogic(const GraphicInterface* gi) {
	this->graphicProvider = gi;
	numCol = 8;
	numRows = 8;

	//Initialize Pointers to invalid address;
	this->player1 = 0;
	this->player2 = 0;
	this->myBoard = 0;
	this->currentPlayer = 0;
};
StandardLogic:: ~StandardLogic() {
}
void StandardLogic::startGame(Player *p1, Player *p2) {
	player1 = p1;
	player2 = p2;
	currentPlayer = p1;
	this->setBoard();
}

bool StandardLogic::gameEnded(void) {
	return (((getValidPositions(player1, this->myBoard)).empty())
			&& ((getValidPositions(player2, this->myBoard)).empty()));
}

Player* StandardLogic::getWinner(void) {
	this->graphicProvider->displayBoard(*myBoard);
	char winner;
	int winnerPoints = 0;
	map<char, int> pointsPerPlayer;
	//Counts the chars
	for (int i = 0; i < this->myBoard->getNumRows() ; i++) {
		for(int j = 0; j < this->numCol ; j++) {
			char dummy = this->myBoard->getCellValue(i, j);
			//Adds to the respective player's char
			pointsPerPlayer[dummy]++;
			if (dummy != ' ' && pointsPerPlayer[dummy] > winnerPoints) {
				winner = dummy;
				winnerPoints = pointsPerPlayer[dummy];
			}
		}
	}
	//If tie
	if (pointsPerPlayer[player1->getPlayerIdChar()] == pointsPerPlayer[player2->getPlayerIdChar()]) {
		return 0;
	}
	//No tie
	else if (winner == player1->getPlayerIdChar()) {
		return player1;
	} else {
		return player2;
	}
}

void StandardLogic::playNextTurn(void) {
	this->graphicProvider->displayBoard(*myBoard);
	vector<Cell> validPositions = this->getValidPositions(this->currentPlayer, this->myBoard);
	if(!validPositions.empty()) {
		this->graphicProvider->displayMessage("It's ");
		this->graphicProvider->displayPlayer(currentPlayer);
		this->graphicProvider->displayMessage("turn, the available positions are:  ");
		this->graphicProvider->displayMoves(validPositions);
		pair<int,int> playerChoice = currentPlayer->makeMove();
		//Check for valid input
		if (!(playerChoice.first < this->numRows && playerChoice.second < this->numCol)) {
			this->graphicProvider->displayMessage("Invalid choice, try again!\n");
			this->playNextTurn();
		}
		else if(!(this->myBoard->getCell(playerChoice.first, playerChoice.second)->getValue() == ' ')) {
			this->graphicProvider->displayMessage("Invalid choice, try again!\n");
			this->playNextTurn();
		} else if(!this->isPositionValid(Cell(playerChoice.first, playerChoice.second, ' '), currentPlayer, this->myBoard)) {
			this->graphicProvider->displayMessage("Invalid choice, try again!\n");
			this->playNextTurn();
		} else { //Valid choice
			Cell dummy = Cell(playerChoice.first, playerChoice.second, ' ');
			this->convertAndSpread(this->myBoard, dummy, currentPlayer);
			this->graphicProvider->displayPlayer(currentPlayer);
			this->graphicProvider->displayMessage("played: ");
			this->graphicProvider->displayCoordinate(playerChoice.first, playerChoice.second);
			this->graphicProvider->displayMessage("\n");
			if (this->currentPlayer == this->player1) {
				this->currentPlayer = player2;
			} else {
				this->currentPlayer = player1;
			}
		}
	} else {
		this->graphicProvider->displayPlayer(currentPlayer);
		this->graphicProvider->displayMessage("\n");
		this->graphicProvider->displayMessage("You are out of plays!\n");
		if (this->currentPlayer == this->player1) {
			this->currentPlayer = player2;
		} else {
			this->currentPlayer = player1;
		}
	}
}


Board StandardLogic::setBoard() {
		this->myBoard = new Board(this->numRows, this->numCol);
		this->myBoard->getCell(myBoard->getNumRows()/2 -1, myBoard->getNumRows()/2 - 1)->setValue('X');
		myBoard->getCell(myBoard->getNumRows()/2, myBoard->getNumCol()/2)->setValue('X');
		myBoard->getCell(myBoard->getNumRows()/2 -1, myBoard->getNumCol()/2)->setValue('O');
		myBoard->getCell(myBoard->getNumRows()/2, myBoard->getNumRows()/2 - 1)->setValue('O');
		return *(this->myBoard);
}

bool StandardLogic::isPositionValid(Cell c, Player *player, Board *gameBoard) {
	// temp is bigger than one if opponent's pieces were caught in between the beginning and end of the path
		char target = player->getPlayerIdChar();
		vector<Cell> temp;
		Cell start = c;
		temp = checkUp(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkDown(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkLeft(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkRight(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkRight(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkDigRightUp(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkDigRightDown(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkDigLeftDown(start, target, gameBoard);
		if (temp.size() > 1) {
			return true;
		}
		temp = checkDigLeftUp(start, target, gameBoard);
		if (temp.size() > 1) {
				return true;
		}
		return false;;
}

vector<Cell> StandardLogic::generalCheck(Board *gameBoard, Cell start, char target, int rowDif, int colDif) {
					int i = 0;
					int j = 0;
					vector<Cell> conversionPath;
					Cell *c = gameBoard->getCell(start.getXCord() + i, start.getYCord() + j); //Get the cell
					if (c == 0) { // If out of bounds
						return conversionPath;
					}
					bool keepChecking = true;
					while(keepChecking) {
						i = i + rowDif; // Adapts to desired direction
						j = j + colDif; // Adapts to desired direction
						c = gameBoard->getCell(start.getXCord() + i, start.getYCord() + j); //Get the cell
						if (c == 0) { // If out of bounds
							keepChecking = false;
							conversionPath.clear();
						}
						else if (c->getValue() == target){ //If target acquired
							conversionPath.push_back(*c);
							keepChecking = false;
						} else if (c->getValue() == start.getValue()){ // If undesired symbol
							conversionPath.clear();
							keepChecking = false;
						} else {
							conversionPath.push_back(*c);
						}
					}
					return conversionPath;
		}

vector<Cell> StandardLogic::getValidPositions(Player *player, Board *gameBoard) {
	vector<Cell> validPositions;
	for (int i = 0; i < gameBoard->getNumRows(); i++) {
		for (int j = 0; j < gameBoard->getNumCol(); j++) {
			Cell *c = gameBoard->getCell(i,j);
			if(c->getValue() == ' ') {
				if( this->isPositionValid(*c,player, gameBoard)) {
					validPositions.push_back(*c);
				}
			}

		}
	}
	sort(validPositions.begin(), validPositions.end());
	return validPositions;
}


vector<Cell> StandardLogic::checkUp(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, 1, 0);
}

vector<Cell> StandardLogic::checkDown(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, -1, 0);
}

vector<Cell> StandardLogic::checkLeft(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, 0, -1);
}

vector<Cell> StandardLogic::checkRight(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, 0, 1);
}

vector<Cell> StandardLogic::checkDigRightUp(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, 1, 1);
}

vector<Cell> StandardLogic::checkDigRightDown(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, -1, 1);
}

vector<Cell> StandardLogic::checkDigLeftUp(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, 1, -1);
}

vector<Cell> StandardLogic::checkDigLeftDown(Cell start, char target, Board *gameBoard) {
return generalCheck(gameBoard, start, target, -1, -1);
}

void StandardLogic::endGame() {
	delete myBoard;
	myBoard = 0;
}

void StandardLogic::convertAndSpread(Board *gameBoard, Cell start, Player *player) {
	gameBoard->setCell(start.getXCord(),start.getYCord(), player->getPlayerIdChar());
	//modifies the start symbol, for it's just a copy
	start.setValue(player->getPlayerIdChar());
	this->propagateConversion(start, gameBoard);
}

void StandardLogic::propagateConversion(Cell start, Board *gameBoard) {
	//Converts all the possible paths in any of the 8 possible directions
	char value = start.getValue();
	convertPath(checkUp(start, value, gameBoard),value, gameBoard);
	convertPath(checkLeft(start, value, gameBoard),value, gameBoard);
	convertPath(checkRight(start, value, gameBoard),value, gameBoard);
	convertPath(checkDown(start, value, gameBoard),value, gameBoard);
	convertPath(checkDigLeftUp(start, value, gameBoard),value, gameBoard);
	convertPath(checkDigLeftDown(start, value, gameBoard),value, gameBoard);
	convertPath(checkDigRightDown(start, value, gameBoard),value, gameBoard);
	convertPath(checkDigRightUp(start, value, gameBoard),value, gameBoard);
}

//propagateConversion subroutine
void StandardLogic::convertPath(vector<Cell> path, char value, Board *gameBoard) {
	if (!path.empty()) {
		for (unsigned int i = 0; i < (path.size()); i++) {
			Cell c = path.at(i);
			gameBoard->setCell(c.getXCord(),c.getYCord(), value);
		}
	}
}

Board* StandardLogic::getBoard() const {
	return this->myBoard;
}


