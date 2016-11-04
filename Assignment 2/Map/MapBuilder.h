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
	Map* getMap();
	void createMap();
	virtual void configMap() = 0;

private:
	Map* map;

};

class NextMapBuilder : public MapBuilder {

public:
	virtual void configMap();

};

class LoadEditedMapBuilder : public MapBuilder {

public:
	virtual void configMap();

};

class MapGenerator {

public:
	void setMapBuilder(MapBuilder* mb);
	Map* getMap();
	void constructMap();

private:
	MapBuilder* mapBuilder;
};