#ifndef DECK_H
#define DECK_H

#include "Card.h"

using namespace std;

#define NUMCARDS 52

class Deck{
private:
	Card cards[NUMCARDS];
	int n_cards;
public:
	// Set number of cards
	void set_n_cards(int);
	// Get n_cards
	int get_n_cards() const;

	void print_deck() const;

	Card return_card(int);
	//Default constructor
	Deck();

	// Shuffle the deck of cards
	void shuffle();
	void remove_card();
};

#endif