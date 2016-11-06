//! @file
//! @brief Implementation file for the Item class
//!
#pragma once
#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

//! Class implementing a game map
class MapBuilder {
public:
	MapBuilder(string fn) {
		ifstream readJsonFile(fn);
		json mapConfig(readJsonFile);
		width = int(mapConfig["mapWidth"]);
		length = int(mapConfig["mapLength"]);
		string pl = mapConfig["placement"];
		placement = pl;
		readJsonFile.close();
	}
	Map* getMap() {
		return m_map;
	};
	void createMap() {
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
	virtual void configMap() = 0;
protected:
	Map* m_map;
	int width, length;
	string placement;
};

class LoadEditedMapBuilder : public MapBuilder {
public:
	LoadEditedMapBuilder(string fn) : MapBuilder(fn) {};
	virtual void configMap() {
		m_map->setMapLevel(0);
	};
};

class NextMapBuilder : public MapBuilder {
public:
	NextMapBuilder(string fn) : MapBuilder(fn) {};
	virtual void configMap() {
		ifstream readJsonFile("character.json");
		json character(readJsonFile);
		readJsonFile.close();
		m_map->setMapLevel(int(character["level"]));
	};
};

class MapGenerator {
public:
	void setMapBuilder(MapBuilder* mb) {
		m_mapBuilder = mb;
	};
	Map* getMap() {
		return m_mapBuilder->getMap();
	};
	void constructMap() {
		m_mapBuilder->createMap();
		m_mapBuilder->configMap();
	};
private:
	MapBuilder* m_mapBuilder;
};