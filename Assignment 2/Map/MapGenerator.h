//! @file
//! @brief Implementation file for the Item class
//!
#pragma once
#include "MapBuilder.cpp"

class MapGenerator {

public:
	void setMapBuilder(MapBuilder* mb);
	Map* getMapBuilder();
	void constructMap();

private:
	MapBuilder* mapBuilder;
};
