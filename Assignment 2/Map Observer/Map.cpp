//! @file
//! @brief Implementation file for the Map class
//!
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include "Map.h"
using std::cout;
using std::endl;
using std::find;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

//! Implementation of the Map class default const a map grid based on default size values
Map::Map() {
  // Default map size is 5x5ructor, creates
  mapWidth = 5;
  mapLength = 5;
  vector<char> row;

  for (int i = 0; i < mapWidth; i++) {
    row.push_back(' ');
  }
  for (int i = 0; i < mapLength; i++) {
    map.push_back(row);
  }
}

//! Implementation of a Map class non-default constructor, creates a map grid based on provided size values
//! @param width: an integer value of horizontal size of the map's grid
//! @param length: an integer value of vertical size of the map's grid
Map::Map(int width, int length) {
  // Default map size is 5x5
  mapWidth = width;
  mapLength = length;
  vector<char> row;

  currentPosition[0] = 0; //represents x
  currentPosition[1] = 0; //represents y

  for (int i = 0; i < mapWidth; i++) {
    row.push_back(' ');
  }
  for (int i = 0; i < mapLength; i++) {
    map.push_back(row);
  }

  setCharacter(currentPosition[0], currentPosition[1]);
  setWall(4, 4);
  setWall(4, 5);
  setWall(5, 4);
  setWall(5, 5);
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

void Map::moveLeft()
{
	if (currentPosition[1] == 0)
	{
		cout << "Cannot move left, please select a different direction." << endl;
	}
	else 
	{
		clearCell(currentPosition[0], currentPosition[1]);
		currentPosition[1]--;
		setCharacter(currentPosition[0], currentPosition[1]);
	}
}

void Map::moveRight()
{
	if (currentPosition[1] == (mapWidth-1))
	{
		cout << "Cannot move right, please select a different direction." << endl;
	}
	else
	{
		clearCell(currentPosition[0], currentPosition[1]);
		currentPosition[1]++;
		setCharacter(currentPosition[0], currentPosition[1]);
	}
}

void Map::moveUp()
{
	if (currentPosition[0] == 0)
	{
		cout << "Cannot move up, please select a different direction." << endl;
	}
	else
	{
		clearCell(currentPosition[0], currentPosition[1]);
		currentPosition[0]--;
		setCharacter(currentPosition[0], currentPosition[1]);
	}
}

void Map::moveDown()
{
	if (currentPosition[0] == (mapLength-1))
	{
		cout << "Cannot move down, please select a different direction." << endl;
	}
	else
	{
		clearCell(currentPosition[0], currentPosition[1]);
		currentPosition[0]++;
		setCharacter(currentPosition[0], currentPosition[1]);
	}
}

void Map::setCharacter(int x, int y)
{
	fillCell(x, y, 'C');
}

void Map::setWall(int x, int y)
{
	fillCell(x, y, 'W');
}

void Map::setStart(int x, int y)
{
	fillCell(x, y, 'S');
}

void Map::setEnd(int x, int y)
{
	fillCell(x, y, 'E');
}

void Map::clearCell(int x, int y)
{
	map[x][y] = ' ';
}

//! Implementation of the map verification
//! @return bool value, true of the map is valid (there is at least one clear path between the mandatory begin and end cell).
bool Map::validatePath() {
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
  vector<pair<int,int>> exploredEmptyCells;
  for (int i = 0; i < (int)startCells.size(); i++) {
    exploredEmptyCells.push_back(startCells[i]);
  }

  // Adds all explorable cells to exploredEmptyCells (unique)
  for (int i = 0; i < (int)exploredEmptyCells.size(); i++) {
    int x = exploredEmptyCells[i].first;
    int y = exploredEmptyCells[i].second;
    char type = ' ';
    if (x > 0) {
      if (map[x-1][y] == type &&
          find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x-1,y)) != exploredEmptyCells.end()) {
        exploredEmptyCells.push_back(make_pair(x-1,y));
      }
    }
    if (x < mapWidth-1) {
      if (map[x+1][y] == type &&
          find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x+1,y)) != exploredEmptyCells.end()) {
        exploredEmptyCells.push_back(make_pair(x+1,y));
      }
    }
    if (y > 0) {
      if (map[x][y-1] == type &&
          find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x,y-1)) != exploredEmptyCells.end()) {
        exploredEmptyCells.push_back(make_pair(x,y-1));
      }
    }
    if (y< mapLength-1) {
      if (map[x][y+1] == type &&
          find(exploredEmptyCells.begin(), exploredEmptyCells.end(), make_pair(x,y+1)) != exploredEmptyCells.end()) {
        exploredEmptyCells.push_back(make_pair(x,y+1));
      }
    }
  }

  // Check if there are any exits next to the explorable cells.
  for (int i = 0; i < (int)exploredEmptyCells.size(); i++) {
    bool isNextToExit = isBeside(exploredEmptyCells[i].first, exploredEmptyCells[i].second, 'E');
    if (isNextToExit) {
      cout << "SUCCESS! This map is valid!" << endl;
      return true;
    }
  }

  // Exit is not reachable from explorable path. Invalid.
    cout << "INVALID: Ensure that explorable path is next to an exit." << endl;
    return false;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @param obj: a character value of object that fills the cell
void Map::fillCell(int x, int y, char obj) {
	map[x][y] = obj;
	Notify();
}

//! Implementation occupation of a cell, check if a cell is occupied
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return : a boolean true if the cell is occupeid false otherwise
bool Map::isOccupied(int x, int y) {
	if (map[x][y] != ' '){
		return true;
	}
	return false;
}

//! Implementation of displayMap, displays a representation of the currently stored map to the user.
void Map::displayMap() {
  string topBottomBorder(mapWidth+2, '-');
  // Print top border
  cout << topBottomBorder << endl;
  for (int i = 0; i < mapLength; i++) {
    // Print left border
    cout << "|";
    // Print cells
    for (int j = 0; j < mapWidth; j++) {
      cout << map[i][j];
    }
    // Print right border
    cout << "|" << endl;
  }
  // Print bottom border
  cout << topBottomBorder << endl;
}

//! Implementation of getMapWidth, provides information on map horizontal size.
//! @return : an integer value representing the map grid's width
int Map::getMapWidth() {
  return mapWidth;
}

//! Implementation of getMapLength, provides information on map vertical size.
//! @return : an integer value representing the map grid's length
int Map::getMapLength() {
  return mapLength;
}

