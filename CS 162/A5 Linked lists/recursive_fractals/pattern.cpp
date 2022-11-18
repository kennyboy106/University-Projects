#include "pattern.h"


void pattern(int n, int c){
    // Call top half of fractal
    ascending_pattern(n, c);
    // Call bottom half of fractal
    descending_pattern(n, c);
}

void ascending_pattern(int n, int c){
    /*********************************************************************
    ** Function: Ascending pattern
    ** Description: Prints the top half of the fractal with recursive calls
    ** Parameters: The largest number of stars in the fractal for a row and the
    *  spaces that the largest row should be from the side of the screen
    ** Pre-Conditions: None
    ** Post-Conditions: Prints the top half of the fractal pattern
    *********************************************************************/
    //I have 7 stars to print with 0 spaces in front
    // I can take 7/2 * 2 to get 6 spaces + c total spaces

    // If n is less than 3 (when we get down to last call)
    if(n > 3){

        ascending_pattern(n - 2, c + 2);
        print_basic_shape(n/2 * 2 + c);
        // Print the spaces needed
        for (int i = 0; i < c; ++i)
        {
            cout << " ";
        }
        // Print out the stars needed
        for (int i = 0; i < n; ++i)
        {
            cout << "* ";
        }
        cout << endl;
    }
}

void descending_pattern(int n, int c){
    /*********************************************************************
    ** Function: Descending pattern
    ** Description: Prints the bottom half of the fractal with recursive calls
    ** Parameters: The largest number of stars in the fractal for a row and the
    *  spaces that the largest row should be from the side of the screen
    ** Pre-Conditions: None
    ** Post-Conditions: Prints the bottom half of the fractal pattern
    *********************************************************************/
    // If its greater than 5 stars, then we need another spacer with n - 2 stars
    // after that
    if(n > 5){
        print_basic_shape(n/2 * 2 + c);

        for (int i = 0; i < c + 2; ++i)
        {
            cout << " ";
        }
        for (int i = 0; i < n - 2; ++i)
        {
            cout << "* ";
        }
        cout << endl;
    }
    // Prevents calling a 5 star line
    if (n > 7)
    {
        descending_pattern(n - 2, c + 2);
    }
    // Should print the last basic shape
    else
    {
        print_basic_shape(n/2 * 2 + c);
    }
}

void print_basic_shape(int spaces){
    /*********************************************************************
    ** Function: Print basic shape
    ** Description: Prints the basic shape separating each line of stars
    ** Parameters: The number of spaces it should be from the screen. Spaces should
    *  be counted for the single star line because the 3 star line accounts by
    *  subtracting 2 spaces each time
    ** Pre-Conditions: None
    ** Post-Conditions: Prints the basic shape between each line of the fractal
    *********************************************************************/
    // Prints the 1 star at the top or bottom
    for (int i = 0; i < spaces; ++i)
    {
        cout << " ";
    }
    cout << "*" << endl;

    // Prints the center three stars with x spaces before the star
    for (int i = 0; i < spaces - 2; ++i)
    {
        cout << " ";
    }
    cout << "* * * " << endl;


    // Prints the 1 star at the top or bottom
    for (int i = 0; i < spaces; ++i)
    {
        cout << " ";
    }
    cout << "*" << endl;
}
