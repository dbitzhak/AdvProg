
#include "Cell.h"
#include <iostream>

using namespace std;


Cell::Cell(int x, int y, char v): value(v), xCord(x), yCord(y){}
Cell::Cell(): value('X'), xCord(0), yCord(0) {}


char Cell::getValue() const {
	return value;
}


void Cell::setValue(char value) {
	this->value = value;
}

bool Cell::isSameValue(char c) {
	return (c == this->value);
}


void Cell::printCell() {
	cout << "(" << this->xCord << "," << this->yCord << ")";
}


int Cell::getXCord() const {
	return this->xCord;
}


int Cell::getYCord() const {
	return this->yCord;
}


bool Cell::sameCoord(Cell c) {
	if (c.getXCord() == getXCord()) {
		return (c.getYCord() == getYCord());
	}
	return false;
}

bool Cell::operator <(const Cell &compareCell) const {
	if(this->getXCord() == compareCell.getXCord()) {
		return (this->getYCord() < compareCell.getYCord());
	} else {
		return (this->getXCord() < compareCell.getXCord());
	}
}

bool Cell::operator ==(const Cell& compareCell) const {
	if(this->getXCord() == compareCell.getXCord()) {
		return (this->getYCord() == compareCell.getYCord());
	} else {
		return false;
	}
	
	
}
