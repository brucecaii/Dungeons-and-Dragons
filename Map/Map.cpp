//! @file 
//! @brief Implementation file for the Map class  
//!
#include "Map.h"

//! constant for map length
int const MAP_LENGTH = 2;
//! constant for map width
int const MAP_WIDTH = 2;
//! map as a 2-dimensional array of chars
char map[MAP_LENGTH][MAP_WIDTH] = {
		{ ' ', ' '}, 
		{' ', ' '} 
	};

//! Implementation of the map verification
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell). 
bool Map::validatePath()
{
	//should test if there is a valid path
	//this stub only returns true
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::fillCell(int x, int y, char obj)
{
	map[x][y] = obj;
}

//! Implementation occupation of a cell, check if a cell is occupied
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a boolean true if the cell is occupeid false otherwise
bool Map::isOccupied(int x, int y)
{
	if (map[x][y] != ' '){
		return true;
	}
	return false;
}
