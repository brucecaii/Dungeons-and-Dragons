//! @file
//! @brief Implementation file for the Map class
//!
#include "MapBuilder.h"

//! get the built dungeons map from the builder
Map* MapBuilder::loadDungeons() {
	return dungeons;
}

//! build a generic empty dungeons map
void MapBuilder::buildGenericDungeons() {
	dungeons = new Map();
}

//! build a dungeons with specific params
void MapBuilder::buildNewDungeons(int width, int length) {
	dungeons = new Map(width, length);
}

//! fill the grid with elements
void MapBuilder::setupDungeons(int x, int y, char obj) {
	dungeons -> fillCell(x, y, obj);
}

class LoadSaveMapBuilder : public MapBuilder {

public:
	LoadSaveMapBuilder() {
		int width, length;
		ifstream saveFile("save.txt");
		saveFile >> width >> length;
		buildNewDungeons(width, length);
		saveFile.close();
	};
	void setDungeons() {
		int width, length;
		string config;
		ifstream saveFile("save.txt");
		saveFile >> width >> length >> config;
		for (int i = 0; i < config.length; i++) {
			char marker = config[i];
			int row = i / width;
			int col = i%width;
			setupDungeons(row, col, marker);
		}
		saveFile.close();
	}
};

class LoadConfigMapBuilder : public MapBuilder {

public:
	LoadConfigMapBuilder() {
		int width, length;
		ifstream mapConfigFile("editedMap.txt");
		mapConfigFile >> width >> length;
		buildNewDungeons(width, length);
		mapConfigFile.close();
	};
	void setDungeons() {
		int width, length;
		string config;
		ifstream mapConfigFile("editedMap.txt");
		mapConfigFile >> width >> length >> config;
		for (int i = 0; i < config.length; i++) {
			char marker = config[i];
			int row = i / width;
			int col = i%width;
			setupDungeons(row, col, marker);
		}
		mapConfigFile.close();
	}
};