#include "entity_functions.h"

bool tile_has_bee(vector<Piece*> ent){
	/*********************************************************************
	** Function: Tile has bee
	** Description: Take in the specific tile pointer (ie GM[x][y]->ent)
	** Parameters: The tile for detection
	** Pre-Conditions: Tile is defined
	** Post-Conditions: Returns true or false if a bee is present
	*********************************************************************/
	for (int i = 0; i < ent.size(); ++i)
	{
		if(ent[i]->get_name().compare("bee") == 0){
			return true;
		}
	}
	return false;
}
