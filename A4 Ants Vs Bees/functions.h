#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "piece.h"
#include "tile.h"
#include "bee.h"
#include "ant.h"


using namespace std;


// void create_board(vector <vector<vector<Piece>>> &);

// Tile** create_board(int*);
	// Making Ants and Bees //
void add_bee(vector<vector<Tile*>>);
void add_ant(vector<vector<Tile*>>);
void try_to_place_ant(vector<vector<Tile*>>, int, Piece*);
Piece* make_ant(int);
int get_positive_int(int, int limit = 999);

	// Turns of Ants and Bees //
void ant_attack(vector<vector<Tile*>>);
void bee_attack(vector<vector<Tile*>>);
void check_type_armor(vector<vector<Tile*>>, string);



bool victory_condition(vector<vector<Tile*>>);
bool bee_win(vector<vector<Tile*>>);

// Utility //
bool validint(string i);
void display_board(vector<vector<Tile*>>);
void print_tiles(vector<Tile*>, int, int);
void print_col_names(int, int);
void standard_spacing(string, int, int);
void print_top_header(int, int);
void print_ant_types();
bool play_again();
bool tile_empty(vector<vector<Tile*>> GB, int x, int y, int ant_type);
void ant_order(vector<Piece*>);



#endif