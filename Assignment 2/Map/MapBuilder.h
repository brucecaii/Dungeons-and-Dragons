//! @file
//! @brief Implementation file for the Item class
//!
#pragma once
#include "Map.h"
#include <fstream>
#include <string>
using namespace std;

//! Class implementing a game map
class MapBuilder {

public:
	Map* loadDungeons();
	void buildGenericDungeons();
	void buildNewDungeons(int width, int length);
	void setupDungeons(int x, int y, char obj);
	virtual void setDungeons() = 0;

private:
	Map* dungeons;
};

