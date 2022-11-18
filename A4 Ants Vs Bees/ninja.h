#ifndef NINJA_H
#define NINJA_H
#include <iostream>
#include "ant.h"


using namespace std;

class Ninja: public Ant {
public:
	// Default constructor
	Ninja();
	// Non default constructor
	Ninja(int);
	// Destructor
	~Ninja();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif