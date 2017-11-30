#include "MachinePlayer.h"
#include <vector>
#include <utility>

using namespace std;
MachinePlayer::MachinePlayer(GameLogic* gl, const GraphicInterface* gi,char value) :
graphicProvider(gi), currentGameLogic(gl) {
	this->setPlayerId(value);
}


std::pair<int, int> MachinePlayer::makeMove() {
	return findBestMove();
}

std::pair<int, int> MachinePlayer::findBestMove() {
	Cell *bestPlay;
	int smallestEnemyScore = (currentGameLogic->getBoard()->getNumCol())
			* (currentGameLogic->getBoard()->getNumRows());
	int currentScore;
	Player *myself = this;
	Board *initialBoard = this->currentGameLogic->getBoard();
	Board *tempBoard;
	vector<Cell> tempPositions = this->currentGameLogic->getValidPositions(this, initialBoard);
	//Parse through the valid positions choosing the one with the lowest max number of pieces for the enemy
	for (unsigned int i = 0; i < tempPositions.size(); i++) {
		tempBoard = new Board(*initialBoard);
		Cell dummy = tempPositions.at(i);
		//Makes the play on a copy of the Board
		currentGameLogic->convertAndSpread(tempBoard, dummy,myself);
		currentScore = this->findOpponentMaxCells(*tempBoard);
		if (currentScore <= smallestEnemyScore) {
			smallestEnemyScore = currentScore;
			bestPlay = &tempPositions.at(i);
		}
		delete tempBoard;
	}
	return make_pair(bestPlay->getXCord(), bestPlay->getYCord());
}

int MachinePlayer::countEnemyCells(Board b, Player *enemy) {
	int counter = 0;
	for (int i = 0; i < b.getNumRows(); i++) {
			for (int j = 0; j < b.getNumCol(); j++) {
				if (b.getCellValue(i,j) == enemy->getPlayerIdChar()) {
					counter++;
				}
			}
	}
	return counter;
}

int MachinePlayer::findOpponentMaxCells(Board targetBoard) {
	char enemyChar;
	Player *enemyDummy = 0;
	Board *pointToTarget;
	//Finds enemy symbol
	for (int i = 0; i < targetBoard.getNumRows(); i++) {
		for (int j = 0; j < targetBoard.getNumCol(); j++) {
			enemyChar = targetBoard.getCellValue(i,j);
			if ((enemyChar != ' ') && (enemyChar != this->getPlayerIdChar())) {
				i = targetBoard.getNumRows();//Stops the outer loop
				j = i; //leaves the inner loop
			}
		}
	}
	//Creates enemy simulation
	MachinePlayer mp(this->currentGameLogic, this->graphicProvider, enemyChar);
	enemyDummy = &mp;
	//
	int bestMoveScore = 0;
	int currentMoveScore = 0;
	pointToTarget = &targetBoard;
	vector<Cell> tempPositions = this->currentGameLogic->getValidPositions(enemyDummy, pointToTarget);
	//Loops through all enemy plays
	Board *tempBoard;
	for (unsigned int i = 0; i < tempPositions.size(); i++) {
		tempBoard = new Board(targetBoard);
		Cell dummy = tempPositions.at(i);
		currentGameLogic->convertAndSpread(tempBoard, dummy,enemyDummy);
		currentMoveScore = countEnemyCells(*tempBoard,enemyDummy);
		delete tempBoard;
		//Updates the highest score
		if (currentMoveScore >= bestMoveScore) {
			bestMoveScore = currentMoveScore;
		}
	}
	return bestMoveScore;

}
