#ifndef GAME_H
#define GAME_H

#include "Card.h"
#include "Deck.h"
#include "Hand.h"
#include "Player.h"
#include "Game.h"

#include <iostream>

class Game{
private:
	Deck cards; //Non-dynamic deck object which will create a 52 card shuffled deck
	Player players[2];
	string argument;
public:

	// Default Constructor
	Game();
	// Non-default Constructor
	Game(int, char**);

	void play_game();
	void deal();
	void sort_hands();
	void draw_a_card(int);
	// Choice between which fishing card function
	Card fishing_card(int);
	// Computer looking for a card to ask for
	Card c_fishing_card();
	// Player looking for a card to ask for
	Card p_fishing_card();
	void go_fish(int, string);
	void seek_and_swap(Card, int, int, int&, int&);
	void card_transfer(int, int, int&, int&, int&);


	// Turns
	void player_turn(int);
	void check_books(int);

	void print_hand_and_book(int);



	void end_game(int&);
	void reset_game();
	void winner();
	void play_again(int&);
};
#endif
