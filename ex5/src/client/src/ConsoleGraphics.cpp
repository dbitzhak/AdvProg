

#include "Board.h"
#include "ConsoleGraphics.h"
#include "Player.h"
#include <vector>
#include <iostream>
using namespace std;

ConsoleGraphics::ConsoleGraphics(void) {};

ConsoleGraphics::~ConsoleGraphics(void) {};


void ConsoleGraphics::displayBoard(Board b) const {
	//Prints the top numbers
			cout << " |";
			for (int j = 0; j < b.getNumCol(); j++ ) {
				cout << " " <<  j << " |";
			}
			cout << endl;
			cout << "--"; //Starts the line
			for (int j = 0; j < b.getNumCol(); j++ ) {
					cout << "----";
				}
			cout <<endl;

			//Prints the rest of the table
			for (int i = 0; i < b.getNumRows(); i++ ) {
				cout << i << "|"; //Prints the row number
				for (int j = 0; j <b.getNumCol(); j++ ) { //Prints the chars
					cout << " " << b.getCellValue(i,j) << " |";
				}
				cout << endl;
				cout << "--"; //Starts the line
					for (int j = 0; j < b.getNumCol(); j++ ) {
							cout << "----";
						}
				cout << endl;
			}
}

void ConsoleGraphics::displayMoves(std::vector<Cell> availablePositions) const {
	cout << endl;
	for (unsigned int i= 0; i < availablePositions.size(); i++) {
				availablePositions.at(i).printCell();
	}
	cout << endl;

}

void ConsoleGraphics::displayMessage(std::string message) const {
	cout << message;
}

void ConsoleGraphics::displayMessage(char message) const {
	cout << message;
}

void ConsoleGraphics::displayPlayer(Player *player) const {
	if (player == 0) {
		cout << "Congratulations to both players!\n" << "It was a tie." << endl;
	} else {
		cout << "Player(" << player->getPlayerIdChar() << ")";
	}
}

void ConsoleGraphics::displayCoordinate(int a, int b) const {
	cout <<"(" << a << "," << b << ") ";
}

