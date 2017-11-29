/*
 * Game.cpp
 *  Author: Daniel Ben Itzhak
 *      338017437
 */

#include "Game.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "GameLogic.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"

#include <iostream>
#include <string>
#include "StandardLogic.h"

using namespace std;

Game::Game(GraphicInterface *gi) : graphicProvider(gi) {};

void Game::start() {
		bool gameLoop = true;
		this->graphicProvider->displayMessage("Welcome to Reversi!\n");
		while(gameLoop) {
			//Prints the greetings for the menu
			this->graphicProvider->displayMessage("Would you like to play:\n");
			this->graphicProvider->displayMessage("Standard Game(1)\n");
			this->graphicProvider->displayMessage("Special Rules(2)\n");
			this->graphicProvider->displayMessage("Quit(3)\n");
			int option;
			cin >> option;
			switch(option) {
			case 1: { //Regular Game
					StandardLogic sl(graphicProvider);
					GameLogic *gl = &sl;
					HumanPlayer p1(graphicProvider, 'X');
					Player *hp1 = &p1;
					HumanPlayer p2(graphicProvider,'O');
					Player *hp2 = &p2;
					this->playOneMatch(gl,hp1, hp2);
			}break;
			case 2:{
				StandardLogic sl(graphicProvider);
				GameLogic *gl = &sl;
				HumanPlayer p1(graphicProvider, 'X');
				Player *hp1 = &p1;
				MachinePlayer p2(gl,graphicProvider,'O');
				Player *mp2 = &p2;
				this->playOneMatch(gl,hp1, mp2);
			}break;
			case 3:{ //Breaks the game loop
				gameLoop = false;
			}break;
			default:{
					this->graphicProvider->displayMessage("Invalid option\n");
			}break;

		}

	}
}

void Game::playOneMatch(GameLogic* gl, Player* p1, Player* p2) {
	gl->startGame(p1, p2);
	while(!gl->gameEnded()) {
		gl->playNextTurn();
	}
	Player *winner = gl->getWinner();
	this->graphicProvider->displayMessage("Congratulations ");
	this->graphicProvider->displayPlayer(winner);
	this->graphicProvider->displayMessage("!\nYou are the winner!!!\n");
	gl->endGame();
}

void Game::setGraphicProvider(const GraphicInterface *graphicProvider) {
	this->graphicProvider = graphicProvider;
}
