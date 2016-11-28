/*
#pragma once
#include "Fighter.h"
using namespace std;

class FighterBuilder {

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
*/