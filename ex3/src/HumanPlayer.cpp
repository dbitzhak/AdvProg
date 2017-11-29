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


pair<int, int> HumanPlayer::receivePlayerInput() {
	 this->graphicProvider->displayMessage("Enter a number\n");
	 this->graphicProvider->displayMessage("Row:");
	 int num1 = getNumberFromUser();
	 this->graphicProvider->displayMessage("Column:");
	 this->graphicProvider->displayMessage("\n");

	 int num2 = getNumberFromUser();
	 return make_pair(num1, num2);
}


int HumanPlayer::getNumberFromUser() {
    int num;
    while (true) {

        cin >> num;

        if (!cin.fail()) {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
            return num;
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

