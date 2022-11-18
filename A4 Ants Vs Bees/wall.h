#ifndef WALL_H
#define WALL_H
#include <iostream>
#include "ant.h"


using namespace std;

class Wall: public Ant {
public:
	// Default constructor
	Wall();
	// Non default constructor
	Wall(int);
	// Destructor
	~Wall();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif