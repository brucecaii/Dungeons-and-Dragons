#include "MapGenerator.h"

void MapGenerator::setMapBuilder(MapBuilder* mb) {
	m_mapBuilder = mb;
};
Map* MapGenerator::getMap() {
	return m_mapBuilder->getMap();
};
void MapGenerator::constructMap() {
	m_mapBuilder->createMap();
	m_mapBuilder->configMap();
};