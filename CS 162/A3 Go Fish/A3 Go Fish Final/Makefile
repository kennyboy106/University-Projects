CC = g++ -std=c++11 -g
exe_file = run

all: $(exe_file)


$(exe_file): prog.cpp Card.o Deck.o Hand.o Player.o Game.o
	$(CC) Card.o Deck.o Hand.o Player.o prog.cpp Game.o -o $(exe_file)

Game.o: Game.cpp Game.h
	$(CC) -c Game.cpp

Card.o: Card.cpp Card.h
	$(CC) -c Card.cpp


Deck.o: Deck.cpp Deck.h
	$(CC) -c Deck.cpp

Hand.o: Hand.cpp Hand.h
	$(CC) -c Hand.cpp

Player.o: Player.cpp Player.h
	$(CC) -c Player.cpp






clean:
	rm -f *.o $(exe_file)