#include "pattern.h"
#include <iostream>

using namespace std;

int main(){


	// Pattern //
	cout << "---No error handling per assignment, enter the correct prompts---" << endl;
	cout << "Enter an odd integer for how many stars you want in the max row" << endl;
	cout << "of the fractal: ";
	int stars, col;
	cin >> stars;
	cout << "Enter integer for how many columns you want in the max row" << endl;
	cout << "of the fractal: ";
	cin >> col;
	pattern(stars, col);





}