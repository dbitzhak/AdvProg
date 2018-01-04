#include "Game.h"
#include "GraphicInterface.h"
#include "ConsoleGraphics.h"
#include "GameLogic.h"
#include "Player.h"
#include "HumanPlayer.h"
#include "MachinePlayer.h"
#include "LocalPlayer.h"
#include "RemotePlayer.h"
#include "Client.h"
#include "StandardLogic.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SERVER_STOPPED -777

using namespace std;

Game::Game(GraphicInterface *gi) : graphicProvider(gi) {};

void Game::start() {
	bool validInput = false;
	bool gameLoop = true;
	this->graphicProvider->displayMessage("Welcome to Reversi!\n");
	while(gameLoop) {
		//Prints the greetings for the menu
		this->graphicProvider->displayMessage("Would you like to:\n");
		this->graphicProvider->displayMessage("(1)Play against a friend\n");
		this->graphicProvider->displayMessage("(2)Beat the Computer\n");
		this->graphicProvider->displayMessage("(3)Face an Online Player\n");
		this->graphicProvider->displayMessage("(4)Quit\n");
		int option;
		cin >> option;
		switch(option) {
			case 1: { //Regular Game
				StandardLogic sl(graphicProvider);
				GameLogic *gl = &sl;
				HumanPlayer p1(gl, graphicProvider, 'X');
				Player *hp1 = &p1;
				HumanPlayer p2(gl, graphicProvider,'O');
				Player *hp2 = &p2;
				this->playOneMatch(gl,hp1, hp2);
			}break;
			case 2:{
				StandardLogic sl(graphicProvider);
				GameLogic *gl = &sl;
				HumanPlayer p1(gl, graphicProvider, 'X');
				Player *hp1 = &p1;
				MachinePlayer p2(gl,graphicProvider,'O');
				Player *mp2 = &p2;
				this->playOneMatch(gl,hp1, mp2);
			}break;
			case 3:{
				validInput = false;
				StandardLogic sl(graphicProvider);
				GameLogic *gl = &sl;
				Player *p1;
				Player *p2;
				const char *serverIP = getIP().c_str();
				int serverPort = getPort();
				Client localClient(serverIP,serverPort);
				try {
					localClient.connectToServer();
				} catch(const char *msg) {
					graphicProvider->displayMessage(msg);
					graphicProvider->displayMessage("\n");
					return;
				}
				string name;
				while(!validInput) {
					graphicProvider->displayMessage("Would you like to:\n");
					graphicProvider->displayMessage("(1)Start a new game\n");
					graphicProvider->displayMessage("(2)Join a game\n");
					cin >> option;
					if(option == 1) {
						validInput = true;
						graphicProvider->displayMessage("Name your game (limit 25 characters)\n");
						cin >> name;
						bool error = true;
						
						while(error) {
							error = false;
							try {
								localClient.startNewGame(name);
							} catch(int i) {
								if(i == SERVER_STOPPED) {
									graphicProvider->displayMessage("Server stopped/n");
									return;
								}
							} catch(const char *msg) {
								graphicProvider->displayMessage(msg);
								error = true;
								cin >> name;
							}
						}
					} else if (option == 2) {
						validInput = true;
						
						string gameList;
						try {
							gameList = localClient.joinGame("");
						} catch(const char *msg) {
							graphicProvider->displayMessage(msg);
							return;
						}
						graphicProvider->displayMessage("Which game would you like to join?\n");
						graphicProvider->displayMessage(gameList);
						cin >> name;
						while(localClient.joinGame(name) == "0") {
							graphicProvider->displayMessage("Invalid choice\n");
						}
					}
				
		
				if (option == 1) {
					LocalPlayer lp(gl, localClient, graphicProvider, 'X');
					RemotePlayer rp(gl, localClient, graphicProvider, 'O');
					p1 = &lp;
					p2 = &rp;
				} else {
					LocalPlayer lp(gl, localClient, graphicProvider, 'O');
					RemotePlayer rp(gl, localClient, graphicProvider, 'X');
					p1 = &rp;
					p2 = &lp;
				}
				this->playOneMatch(gl, p1, p2);
				//Informs server game Ended
				try {
					localClient.closeGame(name);
				} catch (exception e) {}
			}break;
			//case 4:{ //Breaks the game loop
			//	gameLoop = false;
			//}break;
			//default:{
			//	this->graphicProvider->displayMessage("Invalid option\n");
			//}break;
		}
	}
}
}


string Game::getIP() {
	ifstream infile;
	
	infile.open("clientconfig.txt");
	if (!infile) {
		cout << "Error opening file\n";
	}
	
	char ip[13];
	infile >> ip;
	ip[12] = '\0';
	
	infile.close();
	return ip;
}

int Game::getPort() {
	ifstream infile;
	
	infile.open("clientconfig.txt");
	if (!infile) {
		cout << "Error opening file\n";
	}
	
	char buffer[20], port[5];
	infile >> buffer >> port;
	port[4] = '\0';
	infile.close();
	
	stringstream s(port);
	int p = 0;
	s >> p;
	return p;
}


void Game::playOneMatch(GameLogic* gl, Player* p1, Player* p2) {
	gl->startGame(p1, p2);
	while(!gl->gameEnded()) {
		gl->playNextTurn();
	}
	gl->endGame();
}

void Game::setGraphicProvider(const GraphicInterface *graphicProvider) {
	this->graphicProvider = graphicProvider;
}
