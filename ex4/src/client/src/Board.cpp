

#include <iostream>
#include <vector>

#include "Board.h"
#include "Cell.h"

using namespace std;


Board::Board(int rows, int columns) : numRows(rows), numCol(columns) {
	// Using a unary vector for safety/ inline practice
	this->_boardCells = vector<Cell>();
	for (int i = 0; i < this->numRows; i++ ) {
		for (int j = 0; j < this->numCol; j++ ) { //Fills it with spaces
			Cell c(i,j,' ');
			this->_boardCells.push_back(c);
		}
	}
}

Board::Board() : numRows(8), numCol(8) {
	// Using a unary vector for safety/ inline practice
	this->_boardCells = vector<Cell>();
	for (int i = 0; i < this->numRows; i++ ) {
		for (int j = 0; j < this->numCol; j++ ) { //Fills it with spaces
			Cell c(i,j,' ');
			this->_boardCells.push_back(c);
		}
	}
}

Board::Board(Board& oldBoard) {
	char copyValue;
	this->numRows = oldBoard.getNumRows();
	this->numCol = oldBoard.getNumCol();
	this->_boardCells = vector<Cell>();
	for (int i = 0; i < this->numRows; i++ ) {
		for (int j = 0; j < this->numCol; j++ ) { //Fills it with spaces
			copyValue =  oldBoard.getCellValue(i,j);
			Cell c(i,j,copyValue);
			this->_boardCells.push_back(c);
		}
	}
	
}


Cell *Board::getCell(int r, int c) {
	//Checks if Cell inside the rowxcolumn space
	if ((r >= 0) && (r < this->numRows) &&
		(c >= 0) && (c < this->numCol)) {
		return &this->_boardCells.at(index(r,c));
	} else {
		return 0;
	}
}


int Board::getNumCol() const {
	return this->numCol;
}

/*******************************************************************************************************************
 *Function name: getNumRow()
 *The input: None
 *The output: Gets the Board's number of rows
 *The function operation: Access the number of rows
 ********************************************************************************************************************/
int Board::getNumRows() const {
	return this->numRows;
}


char Board:: getCellValue(int r, int c) {
	if ((r >= 0) && (r < this->numRows) &&
		(c >= 0) && (c < this->numCol)) {
		Cell temp = this->_boardCells.at(index(r,c));
		return temp.getValue();
	} else {
		return 0;
	}
	
}
/*******************************************************************************************************************
 *Function name: setCell()
 *The input: row and column coordinates, the cell's new character value.
 *The output: Sets the cell value to the given char
 *The function operation: Access and modifies Cell through setter.
 ********************************************************************************************************************/
void Board::setCell(int r, int c, char set) {
	if ((r >= 0) && (r < this->numRows) &&
		(c >= 0) && (c < this->numCol)) {
		(this->_boardCells.at(index(r,c))).setValue(set);
	}
}
