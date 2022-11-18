#ifndef HUNGRYANT_H
#define HUNGRYANT_H
#include <iostream>
#include "ant.h"


using namespace std;

class Hungryant: public Ant {
private:
	int digesting;
public:
	// Default constructor
	Hungryant();
	// Non default constructor
	Hungryant(int);
	// Destructor
	~Hungryant();

	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);
};

#endif