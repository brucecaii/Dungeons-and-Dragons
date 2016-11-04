//! @file
//! @brief Implementation file for the Map class
//!
#include "MapBuilder.h"

//! get the built dungeons map from the builder
Map* MapBuilder::getMap() {
	return map;
}

//! build a dungeons with specific params
void MapBuilder::createMap() {
	map = new Map();
}

void NextMapBuilder::configMap() {
	//TODO
}

void LoadEditedMapBuilder::configMap() {
	//TODO
}

void MapGenerator::setMapBuilder(MapBuilder* mb) {
	mapBuilder = mb;
}
	
Map* MapGenerator::getMap() {
	return mapBuilder -> getMap();
}
	
void MapGenerator::constructMap() {
	mapBuilder->createMap();
	mapBuilder -> configMap();
}
