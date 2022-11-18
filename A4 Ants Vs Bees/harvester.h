#ifndef HARVESTER_H
#define HARVESTER_H
#include <iostream>
#include "ant.h"


using namespace std;

class Harvester: public Ant {
public:
	// Default constructor
	Harvester();
	// Non default constructor
	Harvester(int);
	// Destructor
	~Harvester();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};





#endif