#ifndef THROWER_H
#define THROWER_H
#include <iostream>
#include "ant.h"


using namespace std;

class Thrower: public Ant {
public:
	// Default constructor
	Thrower();
	// Non default constructor
	Thrower(int);
	// Destructor
	~Thrower();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif