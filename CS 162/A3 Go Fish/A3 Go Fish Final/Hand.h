#ifndef HAND_H
#define HAND_H
#include "Card.h"
using namespace std;


class Hand{
private:
	Card* cards;
	int n_cards;
public:

	//Default Constructor
	Hand();

	// Assignment Overload
	const Hand& operator=(const Hand&);

	//De-constructor
	~Hand();

	//Accessor
	int get_n_cards() const;
	Card* get_cards();
	Card get_card(int) const;
	void show_cards() const;
	//Mutator
	void set_n_cards(int);
	void set_cards(Card*);

	//Remove a card function

	//Add a card function
	void add_card(Card);
	void remove_card(Card);
	// Sort cards in hand
	void sort_by_rank();
	void sort_by_suit();

	int num_ranks() const;
	void count_num_ranks(int*);

	int* book_locate();
	void reset();
};

#endif