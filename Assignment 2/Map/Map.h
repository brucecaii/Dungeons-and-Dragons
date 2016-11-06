//! @file
//! @brief Implementation file for the Item class
//!
#pragma once
#include <vector>
#include "content.cpp"
using std::vector;

//! Class implementing a game map
class Map {

  public:
    Map();
    Map(int width, int length);
    bool validatePath();
    void fillCell(int x, int y, char obj);
	void setMonster(int x, int y, Monster* m);
	void setChest(int x, int y, Chest* c);
    bool isOccupied(int x, int y);
    void displayMap();
    int getMapWidth();
    int getMapLength();
	bool isBeside(int x, int y, char type);

  private:
    int mapWidth;
    int mapLength;
    vector<vector<char>> map;
	vector<vector<Monster>> monster;
	vector<vector<Chest>> chest;
};

