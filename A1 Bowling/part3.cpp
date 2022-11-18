#include <iostream>
#include <string>


using namespace std;

int main(){
	/* I need to create an array for number of pins knocked down.
	 * This can't be an array of integers because i need to worry about
	 * X's and -'s.
	 * 	So an array of strings would be better
	 *
	 * Next i need to display the info after each roll
	 *
	 * Next, create another array that contains the final scores for each player
	 * 		can be another array of ints with blanks on frames with strikes
	*/


	cout << "Enter the number of players: ";
	int players = 0;
	cin >> players;	//Assuming good input
	//create a 2D array of ints for the score of each player
	int total[players][10];


	//Array for pins knocked down
	//	should be an arr of strings
	//	should be a 2d array because 2 turns
	//The following code will create and initialize while printing
	// a 2D array of strings

	string score[players][2][10] = {};
	/*
		How can i make this work for dynamically for x people?

	*/
	int scores = 0;

	for(int k = 0; k < players; k++){
		cout << "Player " << k + 1 << endl;
		for(int j = 0; j < 10; j++){
			for(int i = 0; i < 2; i++){
				scores = i + j;
				score[k][i][j] = to_string(scores);
				cout << score[k][i][j] << " ";

			}

			//Calculate total score based on the previous elements of that row
			cout << "Score: ";
			scores = stoi(score[k][0][j]) + stoi(score[k][1][j]);
			total[k][j] = scores;
			cout << total[k][j];
			cout << endl;
		}
	}


}