//! @file
//! @brief Implementation file for the MapGenerator class
//!
#include "MapGenerator.h"

//! Implementation of mapBuilder setter. It assigns a map builder to the builder director.
// @param mb: a map builder pointer that points to a created map builder with specific concreate type
void MapGenerator::setMapBuilder(MapBuilder* mb) {
	m_mapBuilder = mb;
};

//! Implementation of map getter. It gets the map object from the assigned map builder.
// @return a map object that is created by builder
Map* MapGenerator::getMap() {
	return m_mapBuilder->getMap();
};

//! Implementation of map constructor. It creates the map based on builder's specifications.
void MapGenerator::constructMap() {
	m_mapBuilder->createMap();
	m_mapBuilder->configMap();
};