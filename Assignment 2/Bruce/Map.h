//! @file
//! @brief Implementation file for the Map class
//!
#pragma once
#include <vector>
using std::vector;

//! Class implementing a game map
class Map {

  public:
    Map();
    Map(int width, int length);
    bool validatePath();
    void fillCell(int x, int y, char obj);
	void setMapLevel(int level);
	bool isOccupied(int x, int y);
    void displayMap();
    int getMapWidth();
    int getMapLength();
	int getMapLevel();
	bool isBeside(int x, int y, char type);

  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
	int level;
};

