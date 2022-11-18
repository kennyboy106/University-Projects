#include <iostream>
#include <string>


using namespace std;

void changearr(string*** a, int x, int y, int z){
		for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				a[i][j][k] = to_string(i + j + k);
			}
		}
	}
}

string*** createdynmiac(int x, int y, int z){

	string*** a = new string**[x]; //create an array that will carry double pointers.

	for(int i = 0; i < x; i++){
		//Here we set the elements in our array to hold pointers
		a[i] = new string*[y];

		for(int j = 0; j < y; j++){
			//Here we finally set each of the second level arrays to its own array
			a[i][j] = new string[z];
		}
	}
	return a; //return the double pointer (points to start of master array)
}

void delete3Darr(string ***a, int x, int y){
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			delete [] a[i][j];
		}
		delete [] a[i];
	}
	delete [] a;
}

void delete2Darr(int** a, int x){
	for(int i = 0; i < x; i++){
		delete [] a[i];
	}
	delete [] a;
}
int main(){

	int x = 2, y = 3, z = 4;
/*
	string*** a = createdynmiac(x, y, z);
	changearr(a, x, y, z);

	//Print array elements
	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			for(int k = 0; k < z; k++){
				cout << a[i][j][k] << "|";
			}
			cout << endl; //after every row
		}
		cout << endl; //after every set of 2D arrays
	}
	delete3Darr(a, x, y);
*/

	int** intptr = new int*[x];

	for(int i = 0; i < y; i++){
		intptr[i] = new int[y];
	}

	delete2Darr(intptr, x);
	delete intptr;
}


