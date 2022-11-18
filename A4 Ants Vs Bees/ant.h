#ifndef ANT_H
#define ANT_H
#include <iostream>
#include <vector>
#include <string>
#include "piece.h"


using namespace std;

class Ant: public Piece{
protected:
	int armor;
	int cost;
	string name;
public:
	static int food;
	// Default constructor
	Ant();
	// Non default constructor
	Ant(int);
	// Destructor
	virtual ~Ant();

	// Getter
	int get_armor();
	int get_cost();
	string get_name();

	// Dummy function never gets used
	void freeze(int);
	// Virtual functions
	virtual void attack(vector<vector<Tile*>>, int, int, int) = 0;
	virtual void take_dmg(int) = 0;


};





#endif