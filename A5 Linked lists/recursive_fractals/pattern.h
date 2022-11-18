/** Pattern:
 * 		for 3, 2 we have
 * 		3 stars in the largest row and the stars for that row stars after 2 spaces
 *          *
 *        * * *
 *          *
 *
 * 		for 5, 1 we have
 * 		5 stars in the largest row and they starts after 1 space
 *
 *
 *
 *
 *

    *
  * * *
    *

 Top half
     *
   * * *
     *
 * * * * *

Bottom half
     *
   * * *
     *



      *
    * * *    //repeatable section here
      *
  * * * * *  //5 dots (2 less than input)
      *
    * * *    //repeatable section here
      *
* * * * * * *  //7 dots (0 less than input)



*
*/


#ifndef PATTERN_H
#define PATTERN_H
#include <iostream>

using namespace std;

void pattern(int, int);


void ascending_pattern(int, int);
void descending_pattern(int, int);

void print_basic_shape(int);



#endif