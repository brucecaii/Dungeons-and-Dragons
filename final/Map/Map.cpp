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
  bool bIsBeside= false;
  if (x > 0) {
    if (map[x-1][y] == type) {
      bIsBeside= true;
    }
  }
  if (x < mapWidth-1) {
    if (map[x+1][y] == type) {
      bIsBeside= true;
    }
  }
  if (y > 0) {
    if (map[x][y-1] == type) {
      bIsBeside= true;
    }
  }
  if (y< mapLength-1) {
    if (map[x][y+1] == type) {
      bIsBeside= true;
    }
  }

  return bIsBeside;
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

  if (startCells.size() == 0 || endCells.size() == 0) {
    cout << "INVALID: Ensure you have at least an 'S' cell and a 'E' cell." << endl;
    return false;
  }

  // All start cells must be next to walls
  bool bStartBesideWall = false;
  bool bEndBesideWall = false;
  for (int i = 0; i < (int)startCells.size(); i++) {
    bStartBesideWall = isBeside(startCells[i].first, startCells[i].second, 'W');
  }
  for (int i = 0; i < (int)startCells.size(); i++) {
    bEndBesideWall = isBeside(endCells[i].first, endCells[i].second, 'W');
  }

  if (!bStartBesideWall || !bEndBesideWall) {
    cout << "INVALID: Ensure that all start and end cells are next to walls." << endl;
    return false;
  }

  // The wall must be a closed cycle
  // This is an additional feature.
  // Currently not implemented, but to be done in next assignment / in the project.

  // Check if path is clear
  // Seed explored cells with Start cells
  //vector<pair<int,int>> exploredEmptyCells;
  //for (int i = 0; i < (int)startCells.size(); i++) {
    //exploredEmptyCells.push_back(startCells[i]);
  //}

  // Adds all explorable cells to exploredEmptyCells (unique)
  //for (int i = 0; i < (int)exploredEmptyCells.size(); i++) {
    //int x = exploredEmptyCells[i].first;
    //int y = exploredEmptyCells[i].second;
    //char type = ' ';
    //if (x > 0) {
      //if (map[x-1][y] == type &&
          //find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x-1,y)) != exploredEmptyCells.end()) {
        //exploredEmptyCells.push_back(make_pair(x-1,y));
      //}
    //}
    //if (x < mapWidth-1) {
      //if (map[x+1][y] == type &&
          //find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x+1,y)) != exploredEmptyCells.end()) {
        //exploredEmptyCells.push_back(make_pair(x+1,y));
      //}
    //}
    //if (y > 0) {
      //if (map[x][y-1] == type &&
          //find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x,y-1)) != exploredEmptyCells.end()) {
        //exploredEmptyCells.push_back(make_pair(x,y-1));
      //}
    //}
    //if (y< mapLength-1) {
      //if (map[x][y+1] == type &&
          //find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x,y+1)) != exploredEmptyCells.end()) {
        //exploredEmptyCells.push_back(make_pair(x,y+1));
      //}
    //}
  //}

  // Check if there are any exits next to the explorable cells.

  // Exit is not reachable from explorable path. Invalid.
    //cout << "INVALID: Ensure that explorable path is next to an exit." << endl;
    return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::setCell(int x, int y, char obj) {
	this->map[x][y] = obj;
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
//void Map::display() {
  //cout << string(mapWidth+2,'#') << endl;
  //for (int i = 0; i < (int)map.size(); i++) {
    //cout << "#";
    //for (int j = 0; j < (int)map[i].size(); j++) {
      //cout << map[i][j];
    //}
    //cout << "#" << endl;
  //}
  //cout << string(mapWidth+2,'#') << endl;
//}

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
