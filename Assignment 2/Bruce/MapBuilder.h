#pragma once
#include "Map.h"
#include <fstream>
#include <string>
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

class MapBuilder {
public:
	MapBuilder(string fn);
	Map* getMap();
	void createMap();
	virtual void configMap() = 0;
protected:
	Map* m_map;
	int width, length;
	string placement;
};

class LoadEditedMapBuilder : public MapBuilder {
public:
	LoadEditedMapBuilder(string fn);
	virtual void configMap();
};

class NextMapBuilder : public MapBuilder {
public:
	NextMapBuilder(string fn);
	virtual void configMap();
};