#ifndef SNOW_THROWER_H
#define SNOW_THROWER_H
#include <iostream>
#include "ant.h"


using namespace std;

class Snow_thrower: public Ant {
public:
	// Default constructor
	Snow_thrower();
	// Non default constructor
	Snow_thrower(int);
	// Destructor
	~Snow_thrower();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif