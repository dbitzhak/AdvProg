#ifndef BOARD_H_
#define BOARD_H_

#include "Cell.h"
#include <vector>


#include <iostream>

class Board {
public:
	Board();
	/******************************************************
	*Function name: Board()
	*The input: row and column size, 8x8 is default
	*The output: A Board object
	*The function operation: Constructor for Board
	******************************************************/
	Board(int rows, int columns);
	
	/******************************************************
	*Function name: Board()
	*The input: Board
	*The output: A Board object
	*The function operation: Copy Constructor for Board
	******************************************************/
	Board(Board& oldBoard);
	
	/*******************************************************
	*Function name: getCell()
	*The input: row and column coordinates
	*The output: Cell
	*The function operation: Access and retrieves Cell through getter.
	*********************************************************/
	Cell *getCell(int rowNum, int ColNum);
	
	/*******************************************************
	*Function name: getNumCol()
	*The input: None
	*The output: Gets the Board's number of columns
	*The function operation: Access the number of columns
	********************************************************/
	int getNumCol() const;
	
	/*******************************************************
	*Function name: getNumCol()
	*The input: None
	*The output: Gets the Board's number of columns
	*The function operation: Access the number of columns
	********************************************************/
	int getNumRows() const;
	
	/*******************************************************
	*Function name: getCellalue()
	*The input: None
	*The output: Gets the Cell's value
	*The function operation: Return char value
	********************************************************/
	char getCellValue(int row, int col);
	
	/**********************************************************************
	*Function name: setCell()
	*The input: row and column coordinates, the cell's new character value.
	*The output: Sets the cell value to the given char
	*The function operation: Access and modifies Cell through setter.
	************************************************************************/
	void setCell(int row, int col, char set);
	
private:
	//Members
	int numRows;
	int numCol;
	std::vector<Cell> _boardCells; //A vector of Cells
	//Maps x&y coordinates to a single index
	inline int index(int a, int b) {
		return (a * (this->numCol) + b);
	};

	
};

#endif /* BOARD_H_ */

