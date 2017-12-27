#Makefile

a.out: Server.o main.o
	g++ Server.o main.o -o server.out

Server.o: Server.cpp Server.h
	g++ -c Server.cpp

main.o: main.cpp Server.h
	g++ -c main.cpp

run:
	./a.out
