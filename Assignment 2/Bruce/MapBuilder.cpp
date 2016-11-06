#include "MapBuilder.h"

MapBuilder::MapBuilder(string fn) {
	ifstream readJsonFile(fn);
	json mapConfig(readJsonFile);
	width = int(mapConfig["mapWidth"]);
	length = int(mapConfig["mapLength"]);
	string pl = mapConfig["placement"];
	placement = pl;
	readJsonFile.close();
}

Map* MapBuilder::getMap() {
	return m_map;
};
	
void MapBuilder::createMap() {
	m_map = new Map(width, length);
	for (size_t i = 0; i < placement.length(); i++) {
		int currentX, currentY;
		if (i == 0) {
			currentX = 0;
			currentY = 0;
		}
		else {
			currentX = int(i / width);
			currentY = int(i%width);
		}
		const char* obj = placement.c_str();
		m_map->fillCell(currentX, currentY, obj[i]);
	}
};

LoadEditedMapBuilder::LoadEditedMapBuilder(string fn) : MapBuilder(fn) {};

void LoadEditedMapBuilder::configMap() {
	m_map->setMapLevel(0);
};

NextMapBuilder::NextMapBuilder(string fn) : MapBuilder(fn) {};

void NextMapBuilder::configMap() {
	ifstream readJsonFile("character.json");
	json character(readJsonFile);
	readJsonFile.close();
	m_map->setMapLevel(int(character["level"]));
};
