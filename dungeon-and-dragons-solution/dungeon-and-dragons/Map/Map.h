//! @file
//! @brief Header file for the Map class
//!
#pragma once

#include <string>
#include <vector>
#include <tuple>
#include "../Subject.h"

using std::tuple;
using std::string;
using std::vector;

//! Class implementing a game map
class Map : public Subject{
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
    string getMapData();
    void setMapData(string);
    bool isBeside(int x, int y, char type);
    void clearCell(int x, int y);
    vector<tuple<char,int,int>> getAllCharacterPositions();
    vector<int> getHumanPosition();
    void display();
	string getLetterType(char obj);
  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
};
