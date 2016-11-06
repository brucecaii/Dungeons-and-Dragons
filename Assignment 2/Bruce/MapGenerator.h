#pragma once
#include "MapBuilder.h"

class MapGenerator {
public:
	void setMapBuilder(MapBuilder* mb);
	Map* getMap();
	void constructMap();
private:
	MapBuilder* m_mapBuilder;
};