//! @file
//! @brief Implementation file for the Map class
//!
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "Map.h"

using std::cout;
using std::endl;
using std::find;
using std::make_pair;
using std::pair;
using std::string;
using std::make_tuple;
using std::vector;

//! Implementation of the Map class default constructor, creates a map grid based on default size values
Map::Map() {
  // Default map size is 4x4
  this->mapWidth = 4;
  this->mapLength = 4;
  setMapData("                ");
}

//! Implementation of a Map class non-default constructor, creates a map grid based on provided size values
//! @param width: an integer value of horizontal size of the map's grid
//! @param length: an integer value of vertical size of the map's grid
Map::Map(int width, int length, string placement) {
  // Default map size is 5x5
  this->mapWidth = width;
  this->mapLength = length;
  setMapData(placement);
}


//! Implementation of is beside, checks if a specific cell is adjacent (top/left/bottom/right) to a specific cell type.
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return bool value, true if there is a the cell type adjacent to the specific cell chosen
bool Map::isBeside(int x, int y, char type) {
	
	//check top left cell
	if (x == 0 && y == 0) {
		return this->checkRight(x, y, type) || this->checkDown(x, y, type);
	}
	//check top right cell
	else if (x == 0 && y == this->getMapLength()-1) {
		return this->checkLeft(x, y, type) || this->checkDown(x, y, type);
	}
	//check bottom left cell
	else if (x == this->getMapWidth()-1 && y == 0) {
		return this->checkUp(x, y, type) || this->checkRight(x, y, type);
	}
	//check bottom right cell
	else if (x == this->getMapWidth() - 1 && y == this->getMapLength() - 1) {
		return this->checkLeft(x, y, type) || this->checkUp(x, y, type);
	}
	//check left edge
	else if (y == 0) {
		return this->checkUp(x, y, type) || this->checkRight(x, y, type) || this->checkDown(x, y, type);
	}
	//check right edge
	else if (y == this->getMapLength()-1) {
		return this->checkUp(x, y, type) || this->checkLeft(x, y, type) || this->checkDown(x, y, type);
	}
	//check upper edge
	else if (x == 0) {
		return this->checkRight(x, y, type) || this->checkLeft(x, y, type) || this->checkDown(x, y, type);
	}
	//check bottom edge
	else if (x == this->getMapWidth()-1) {
		return this->checkRight(x, y, type) || this->checkLeft(x, y, type) || this->checkUp(x, y, type);
	}
	//middle cells
	else {
		return this->checkRight(x, y, type) || this->checkLeft(x, y, type) || this->checkUp(x, y, type) || this->checkDown(x, y, type);
	}
}

bool Map::checkUp(int x, int y, char type) {
	if (x == 0) return false;
	return this->getCell(x - 1, y) == type;
}
bool Map::checkDown(int x, int y, char type) {
	if (x == this->getMapWidth() - 1) return false;
	return this->getCell(x + 1, y) == type;
}
bool Map::checkLeft(int x, int y, char type) {
	if (y == 0) return false;
	return this->getCell(x, y - 1) == type;
}
bool Map::checkRight(int x, int y, char type) {
	if (y == this->getMapLength() - 1) return false;
	return this->getCell(x, y + 1) == type;
}


//! Implementation of the map verification
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell).
bool Map::validatePath() {
  // Map sure map is large enough. We are using mapWidth>3 and mapLength>3
  if (mapLength < 4 || mapWidth < 4) {
    cout << "INVALID: Map size too small" << endl;
    return false;
  }

  // Find start and end cells
  vector<pair<int,int>> startCells, endCells;

  for (int i = 0; i < mapWidth; i++) {
    for (int j = 0; j < mapWidth; j++) {
      if (map[i][j] == 'S') {
        startCells.push_back(make_pair(i,j));
      }
      if (map[i][j] == 'E') {
        endCells.push_back(make_pair(i,j));
      }
    }
  }

  //check if start and exist 
  if (startCells.size() == 0 || endCells.size() == 0) {
    cout << "INVALID: Ensure you have one 'Start' cell and at least one 'Exit' cell." << endl;
    return false;
  }

  //check if multiple starts
  if (startCells.size() > 1) {
	  cout << "INVALID: Ensure you only have one 'Start' cell." << endl;
	  return false;
  }

  //check if the wall is enclosed.
  for (int k = 0; k < this->getMapWidth(); k++) {
	  for (int l = 0; l < this->getMapLength(); l++) {
		  if (this->getCell(k, l) == 87) {
			  if (!(isBeside(k, l, 87) || isBeside(k, l, 83) || isBeside(k, l, 69))) {
				  cout << "INVALID: Ensure the wall is enclosed (diagonal is not valid)." << endl;
				  return false;
			  }
		  }
	  }
  }

  // Start cell must be next to walls
  bool bStartBesideWall = false;
  bStartBesideWall = isBeside(startCells[0].first, startCells[0].second, 'W');
  bool bEndBesideWall = false;
  for (size_t i = 0; i < startCells.size(); i++) {
    bEndBesideWall = isBeside(endCells[i].first, endCells[i].second, 'W');
  }
  if (!bStartBesideWall || !bEndBesideWall) {
	  cout << "INVALID: Ensure that all start and end cells are next to walls." << endl;
	  return false;
  }

  return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::setCell(int x, int y, char obj) {
	string objName;
	//Human Character has reached the exit, need to be logged correctly
        //if (map[x][y] == 'E' && obj == 'S')
        //{
                //objName = getLetterType(obj);
                //UpdateLog("Map", "setCell", objName + " has moved or set to cell " + to_string(x) + "," + to_string(y));
        //}

	//Set obj to x,y location
	this->map[x][y] = obj;

        //Only logging Character movements in the map
        //if (obj == 'S' || obj == 'O' || obj == 'C') {
                //objName = getLetterType(obj);
                //UpdateLog("Map", "setCell", objName + " has moved or set to cell " + to_string(x) + "," + to_string(y));
        //}
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
char Map::getCell(int x, int y) {
	return this->map[x][y];
}

//! Implementation occupation of a cell, check if a cell is occupied
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a boolean true if the cell is occupeid false otherwise
bool Map::isOccupied(int x, int y) {
	if (this->map[x][y] != ' '){
		return true;
	}
	return false;
}

//! Implementation of getMapWidth, provides information on map horizontal size.
//! @return : an integer value representing the map grid's width
int Map::getMapWidth() {
  return this->mapWidth;
}

//! Implementation of getMapLength, provides information on map vertical size.
//! @return : an integer value representing the map grid's length
int Map::getMapLength() {
  return this->mapLength;
}

//! Implementation of getMapWidth, provides information on map horizontal size.
//! @return : an integer value representing the map grid's width
void Map::setMapWidth(int mw) {
  this->mapWidth = mw;
}

//! Implementation of getMapLength, provides information on map vertical size.
//! @return : an integer value representing the map grid's length
void Map::setMapLength(int ml) {
  this->mapLength = ml;
}

//! Implementation of getMapdata
//@return map data in the form of a vector of vector of chars.
string Map::getMapData() {
  string placement;
  for(int i = 0; i < this->mapWidth; i++) {
    for(int j = 0; j < this->mapLength; j++) {
      placement += this->map[i][j];
    }
  }
  return placement;

}

//! Implementation of setMapdata
void Map::setMapData(string placement) {
  //It relies on this->mapWidth and this->mapLength being previously set!
  int i = 0;
  int j = 0;
  // Preventing segfaults here
  this->map = {{}};
  this->map.resize(this->mapWidth, {});
  for (int z = 0; z < this->mapWidth; z++) {
    this->map[z].resize(this->mapLength,' ');
  }

  for(string::size_type k = 0; k < placement.size(); k++) {
    this->map[i][j] = placement[k];
    j++;
    if (j == this->mapLength) {
      i++;
      j = 0;
    }
    if (i == this->mapWidth) {
      // map was badly configured, truncating here
      break;
    }
  }
}


//! Implementation of the display method. Prints an ASCII map to the console.
/////////////////////////////////////////////////////////////
// SHOULD NO LONGER BE NEEDED WHEN BENNY MERGES HIS LOGGER //
/////////////////////////////////////////////////////////////
void Map::display() {
  cout << string(mapWidth+2,'#') << endl;
  for (int i = 0; i < (int)map.size(); i++) {
    cout << "#";
    for (int j = 0; j < (int)map[i].size(); j++) {
      cout << map[i][j];
    }
    cout << "#" << endl;
  }
  cout << string(mapWidth+2,'#') << endl;
}

string Map::getLetterType(char obj)
{
	string objName;
	if (obj == 'S')
		objName = "Human Character";
	if (obj == 'C')
		objName = "Friendly Character";
	if (obj == 'O')
		objName = "Aggressor Character";

	return objName;
}

void Map::clearCell(int x, int y){
  map[x][y] = ' ';
}

//! Implementation of the getAllCharacterPositions method. This allows for the eventual construction of Character objects that correspond to letters on the map grid.
// @return a vector of tuples, which contain the character type and its position on the map.
vector<tuple<char,int,int>> Map::getAllCharacterPositions() {
  vector<tuple<char,int,int>> characterPositions;
  for(int i = 0; i < this->mapWidth; i++) {
    for(int j = 0; j < this->mapLength; j++) {
      if (map[i][j] == 'S' || map[i][j] == 'C' || map[i][j] == 'O') {
        characterPositions.push_back(make_tuple(map[i][j], i ,j));
      }
    }
  }
  return characterPositions;
}

//! Implementation of the getHumanPosition method. This returns a empty vector if no start character/position is found (technically an invalid map), and a vector 2 ints corresponding to the start position if one is found
// @return a vector of ints corresponding to the start position

vector<int> Map::getHumanPosition() {
  vector<int> humanPosition = {};
  for(int i = 0; i < this->mapWidth; i++) {
    for(int j = 0; j < this->mapLength; j++) {
      if (map[i][j] == 'S') {
        humanPosition.push_back(i);
        humanPosition.push_back(j);
        return humanPosition;
      }
    }
  }
  return humanPosition;
}
