CC = g++ -std=c++11 -g
exe_file = run

all: $(exe_file)


$(exe_file): prog.cpp piece.o functions.o entity_functions.o tile.o Game.o ant.o bee.o harvester.o fire.o thrower.o snow_thrower.o hungryant.o wall.o ninja.o bodyguard.o
	$(CC) prog.cpp piece.o functions.o entity_functions.o tile.o Game.o ant.o bee.o harvester.o fire.o thrower.o snow_thrower.o hungryant.o wall.o ninja.o bodyguard.o -o $(exe_file)

piece.o: piece.cpp piece.h
	$(CC) -c piece.cpp

functions.o: functions.cpp functions.h
	$(CC) -c functions.cpp

entity_functions.o: entity_functions.cpp entity_functions.h
	$(CC) -c entity_functions.cpp

tile.o: tile.cpp tile.h
	$(CC) -c tile.cpp

Game.o: Game.cpp Game.h
	$(CC) -c Game.cpp

ant.o: ant.cpp ant.h
	$(CC) -c ant.cpp

bee.o: bee.cpp bee.h
	$(CC) -c bee.cpp

harvester.o: harvester.cpp harvester.h
	$(CC) -c harvester.cpp

fire.o: fire.cpp fire.h
	$(CC) -c fire.cpp

thrower.o: thrower.cpp thrower.h
	$(CC) -c thrower.cpp

snow_thrower.o: snow_thrower.cpp snow_thrower.h
	$(CC) -c snow_thrower.cpp

hungryant.o: hungryant.cpp hungryant.h
	$(CC) -c hungryant.cpp

wall.o: wall.cpp wall.h
	$(CC) -c wall.cpp

ninja.o: ninja.cpp ninja.h
	$(CC) -c ninja.cpp

bodyguard.o: bodyguard.cpp bodyguard.h
	$(CC) -c bodyguard.cpp





clean:
	rm -f *.o $(exe_file)