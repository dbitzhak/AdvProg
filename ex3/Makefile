#Makefile

a.out: Board.o Cell.o ConsoleGraphics.o Game.o HumanPlayer.o Player.o  StandardLogic.o main.o
	g++ Board.o Cell.o ConsoleGraphics.o Game.o HumanPlayer.o Player.o  StandardLogic.o main.o

main.o: main.cpp Game.h ConsoleGraphics.h GraphicInterface.h
	g++ -c main.cpp

Board.o: Board.cpp Board.h Cell.h
	g++ -c Board.cpp

Cell.o: Cell.cpp Cell.h
	g++ -c Cell.cpp

ConsoleGraphics.o: ConsoleGraphics.cpp ConsoleGraphics.h GraphicInterface.h Player.h Board.h
	g++ -c ConsoleGraphics.cpp

Game.o: Game.cpp Game.h GameLogic.h StandardLogic.h  Player.h GraphicInterface.h GraphicInterface.h ConsoleGraphics.h HumanPlayer.h
	g++ -c Game.cpp

HumanPlayer.o: HumanPlayer.cpp HumanPlayer.h Player.h GraphicInterface.h
	g++ -c HumanPlayer.cpp

Player.o: Player.cpp Player.h Player.h GraphicInterface.h
	g++ -c Player.cpp

StandardLogic.o: StandardLogic.cpp StandardLogic.h GameLogic.h Player.h GraphicInterface.h Board.h Cell.h
	g++ -c StandardLogic.cpp

run:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes --show-below-main=yes ./a.out
