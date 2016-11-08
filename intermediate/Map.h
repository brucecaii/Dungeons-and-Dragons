//! @file
//! @brief Header file for the Map class
//!
#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

//! Class implementing a game map
class Map {
  public:
    Map();
    Map(int width, int length, string placement);
    bool validatePath();
    void setCell(int x, int y, char obj);
    char getCell(int x, int y);
    bool isOccupied(int x, int y);
    int getMapWidth();
    int getMapLength();
    void setMapWidth(int width);
    void setMapLength(int length);
    void setMapLevel(int lv);
    int getMapLevel();
    vector<vector<char>> getMapData();
    bool isBeside(int x, int y, char type);
  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
    int level;
};

