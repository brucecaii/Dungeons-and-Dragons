//! @file
//! @brief Implementation file for the MapBuilder class, LoadEditedMapBuilder class, and NextMapBuilder class.
//!
#include "MapBuilder.h"

//! Implementation of a MapBuilder class non-default constructor, creates a map builder based on provided file name as string and save map config
//! @param fn: a string of file name of saved map config file
MapBuilder::MapBuilder(string fn) {
	ifstream readJsonFile(fn);
	json mapConfig(readJsonFile);
	width = int(mapConfig["mapWidth"]);
	length = int(mapConfig["mapLength"]);
	string pl = mapConfig["placement"];
	placement = pl;
	readJsonFile.close();
}

//! Implementation of a map getter
//! @return Map object that map builder holds
Map* MapBuilder::getMap() {
	return m_map;
};

//! Implementation of a create map function. It create a map based on config size and generate corresponding cell with characters, items, wall, and gates.
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

//! Implementation of a LoadEditedMapBuilder class non-default constructor, creates a map builder based on provided file name as string and save map config
//! @param fn: a string of file name of saved map config file
LoadEditedMapBuilder::LoadEditedMapBuilder(string fn) : MapBuilder(fn) {};

//! Implementation of map level setter. It saves the character's level to the map so its items and characters can take this config to create instances. If it is 0, it means the map is in editing.
void LoadEditedMapBuilder::configMap() {
	m_map->setMapLevel(0);
};

//! Implementation of a NextMapBuilder class non-default constructor, creates a map builder based on provided file name as string and save map config
//! @param fn: a string of file name of saved map config file
NextMapBuilder::NextMapBuilder(string fn) : MapBuilder(fn) {};

//! Implementation of map level setter. It saves the character's level to the map so its items and characters can take this config to create instances. 
void NextMapBuilder::configMap() {
	ifstream readJsonFile("character.json");
	json character(readJsonFile);
	readJsonFile.close();
	m_map->setMapLevel(int(character["level"]));
};
