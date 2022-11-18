#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <vector>
#include "tile.h"
#include "functions.h"

using namespace std;

class Game{
private:
	vector<vector<Tile*>> gameboard;
	int num_rows;
public:
	// Default
	Game();
	// Non default
	Game(int);
	// Destructor
	~Game();
	// Play the game
	void play();
};


#endif