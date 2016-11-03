//! @file
//! @brief Implementation file for the Map class
//!
#include "MapGenerator.h"

void MapGenerator::setMapBuilder(MapBuilder* mb) {
	mapBuilder = mb;
}
	
Map* MapGenerator::getMapBuilder() {
	return mapBuilder -> loadDungeons();
}
	
void MapGenerator::constructMap() {
	mapBuilder -> setDungeons();
}
