#ifndef BEE_H
#define BEE_H
#include <iostream>
#include <vector>
#include <string>
#include "piece.h"
#include "tile.h"


using namespace std;

class Bee: public Piece {
protected:
	int armor;
	string name = "bee";
	int frozen;
public:
	// Default constructor
	Bee();
	// Non default constructor
	Bee(int);
	// Destructor
	~Bee();


	int get_armor();
	int get_cost();
	string get_name();
	// Virtual functions
	void attack(vector<vector<Tile*>>, int, int, int);
	void take_dmg(int);

	// Functions just for bees
	bool tile_available(vector<vector<Tile*>>, int, int);
	void freeze(int);
};





#endif