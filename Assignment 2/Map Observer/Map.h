//! @file
//! @brief Implementation file for the Item class
//!
#pragma once
#include "Subject.h"
#include <vector>
using std::vector;

//! Class implementing a game map
class Map : public Subject{
  public:
    Map();
    Map(int width, int length);
    bool validatePath();
    void fillCell(int x, int y, char obj);
    bool isOccupied(int x, int y);
    void displayMap();
    int getMapWidth();
    int getMapLength();
    bool isBeside(int x, int y, char type);
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void setCharacter(int x, int y);
	void setWall(int x, int y);
	void setStart(int x, int y);
	void setEnd(int x, int y);
	void clearCell(int x, int y);
  private:
    int mapWidth;
    int mapLength;
	int currentPosition[2];
    vector<vector<char>> map;
};

