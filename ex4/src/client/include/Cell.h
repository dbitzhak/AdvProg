#ifndef CELL_H_
#define CELL_H_


#include <iostream>

class Cell {
public:
	Cell();
	/********************************************************************
	*Function name: Cell()
	*The input: row and column coordinates, the cell's character value.
	*The output: Cell object
	*The function operation: Cell Constructor
	*********************************************************************/
	Cell(int x, int y, char v = ' ');
	
	/***********************************************************************
	*Function name: isSameValue()
	*The input: character value.
	*The output: boolean true if it's the same character, false otherwise
	*The function operation: char comparison.
	************************************************************************/
	bool isSameValue(char c);
	
	/******************************************************
	*Function name: getValue()
	*The input: None.
	*The output: Char value of the cell
	*The function operation: Getter method for value.
	********************************************************/
	char getValue() const;
	
	/*****************************************************************
	*Function name: setValue()
	*The input: Desired new cell's value (char).
	*The output: Sets the cell value to the given char
	*The function operation: Access and modifies Cell through setter.
	******************************************************************/
	void setValue(char value);
	
	/*********************************************************************
	*Function name: printCell()
	*The input: None
	*The output: None
	*The function operation: Uses cout to print the cell's coordinates.
	***********************************************************************/
	void printCell();
	
	/***************************************
	*Function name: getXCord()
	*The input: None
	*The output: The cell's xCoord (int)
	*The function operation: Return value.
	*****************************************/
	int getXCord() const;
	
	/******************************************
	*Function name: getYCord()
	*The input: None
	*The output: The cell's yCoord (int)
	*The function operation: Return value.
	********************************************/
	int getYCord() const;
	
	/*****************************************************************************
	*Function name: SameCoord()
	*The input: Cell.
	*The output: boolean true if it's the same coordinates (x,y), false otherwise
	*The function operation: int comparison.
	*******************************************************************************/
	bool sameCoord(Cell c);
	
	/*****************************************************************************
	*Function name: == Operator overloading
	*The input: Cell.
	*The output: boolean true if it's the same coordinates (x,y), false otherwise
	*The function operation: int comparison.
	*******************************************************************************/
	bool operator ==(const Cell &compareCell) const;
	
	/*****************************************************************************
	*Function name: < Operator overloading
	*The input: Cell.
	*The output: boolean true if the x coordinate of the current Cell xCoord is smaller
	than the one received or if the x's are equal but the yCoord of the current Cell smaller.
	False otherwise.
	*The function operation: int comparison.
	*******************************************************************************/
	bool operator <(const Cell &compareCell) const;
	
private:
	//Members
	char value;
	int xCord;
	int yCord;
};

#endif /* CELL_H_ */
