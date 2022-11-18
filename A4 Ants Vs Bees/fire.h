#ifndef FIRE_H
#define FIRE_H
#include <iostream>
#include "ant.h"


using namespace std;

class Fire: public Ant {
public:
	// Default constructor
	Fire();
	// Non default constructor
	Fire(int);
	// Destructor
	~Fire();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif