//! @file 
//! @brief Implementation file for the Item class  
//!
#pragma once

//! Class implementing a game map
class Map
{
public:
	bool validatePath();
	void fillCell(int x, int y, char obj);
	bool isOccupied(int x, int y);
};

