#ifndef TILE_H
#define TILE_H
#include <iostream>
#include <vector>
#include "piece.h"


using namespace std;

class Tile{
public:
	vector<Piece*> ent;
	int num_pieces;
	Tile();
	~Tile();
};



#endif