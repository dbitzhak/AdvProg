/*
 * HumanPlayer.cpp
 *  Author: Daniel Ben Itzhak
 *      338017437
 */

#include "HumanPlayer.h"
#include <iostream>
#include <limits>
#include <utility>

using namespace std;

HumanPlayer::HumanPlayer(const GraphicInterface *gi, char value) :graphicProvider(gi) {
		setPlayerId(value);
}
HumanPlayer::HumanPlayer(): graphicProvider(NULL) {
	setPlayerId('X');
}

pair<int, int> HumanPlayer::receivePlayerInput() {
	 this->graphicProvider->displayMessage("Enter a number(row,column):");
	 return getNumberFromUser();
}


pair<int, int> HumanPlayer::getNumberFromUser() {
    int num1;
    int num2;
    char dummy;
    while (true) {
        cin >> num1 >> dummy >> num2;
        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return make_pair(num1,num2);
        }

        // user didn't input a number
        graphicProvider->displayMessage("Please enter numbers only?\n");
        cin.clear(); // reset failbit
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
    }
}

pair<int, int> HumanPlayer::makeMove() {
	return this->receivePlayerInput();
}

