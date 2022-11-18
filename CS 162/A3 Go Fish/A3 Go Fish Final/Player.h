#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player{
private:
	Hand hand;
	int* books;
	int n_books;
public:

	// Default Constructor
	Player();
	// De-constructor
	~Player();

	// Copy constructor
	Player(const Player&);

	// Assignment overload
	const Player& operator=(const Player&);

	// Add card to pass to hand.h
	void add_card(Card);
	// Remove a certain card from the hand
	void remove_card(Card);

	void add_book(int);
	// Show cards in hand
	void show_hand() const;
	// Show books
	void show_book() const;

	// Get Card at certain point
	Card card_at(int);

	// Sort cards in their hand
	void sort_cards();

	// Check for books
	int* book_locate();
	// Number of ranks in the players hand
	int num_ranks();
	int num_cards();
	int num_books();

	void reset();
};
#endif