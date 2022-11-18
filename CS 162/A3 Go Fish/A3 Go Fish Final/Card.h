#ifndef CARD_H
#define CARD_H
#include <string>

using namespace std;

class Card{
private:
	int rank;
	int suit;


public:

	void set_rank(int);
	void set_suit(int);
	int get_rank() const;
	int get_suit() const;
	string map_suit() const;
	string map_rank() const;
	void print_card() const;
	//constructors
	Card();
	//Copy constructor
	Card(const Card&);
	// Assignment Overload
	const Card& operator=(const Card&);
	Card(int, int);


};



#endif