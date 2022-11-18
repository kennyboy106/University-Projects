#ifndef BODYGUARD_H
#define BODYGUARD_H
#include <iostream>
#include "ant.h"


using namespace std;

class Bodyguard: public Ant {
public:
	// Default constructor
	Bodyguard();
	// Non default constructor
	Bodyguard(int);
	// Destructor
	~Bodyguard();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif