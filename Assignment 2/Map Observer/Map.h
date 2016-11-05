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
  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
};

