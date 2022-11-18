#ifndef PIECE_H
#define PIECE_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;
class Tile;

class Piece{
public:
	Piece();
	virtual ~Piece();
	// Getters
	virtual int get_armor() = 0;
	virtual int get_cost() = 0;
	virtual string get_name() = 0;

	virtual void attack(vector<vector<Tile*>>, int, int, int) = 0;
	virtual void take_dmg(int) = 0;
	virtual void freeze(int) = 0;

};


#endif