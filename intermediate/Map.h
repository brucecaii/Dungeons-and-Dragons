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
    string getMapData();
    void setMapData(string);
    bool isBeside(int x, int y, char type);
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void setCharacter(int x, int y);
    void clearCell(int x, int y);
    void openChest();
    bool setCurrentPosition();
    int getCurrentPositionX();
    int getCurrentPositionY();
  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
    int level;
    int currentPosition[2];
};
