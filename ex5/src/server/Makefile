#Makefile

a.out: main.o Server.o
	g++ -o a.out main.o Server.o

main.o: main.cpp Server.h
	g++ -c -o main.o main.cpp

Client.o: Server.cpp
	g++ -c -o Server.o Server.cpp

run:
	./a.out
