#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>
#include "MapBuilder.h"
using namespace std;

int main() {

	/*
	MapGenerator mapGenerator;
	MapBuilder* nextLevelMapBuilder = new NextMapBuilder();
	MapBuilder* loadEditMapBuilder = new LoadEditedMapBuilder();
	
	mapGenerator.setMapBuilder(nextLevelMapBuilder);
	mapGenerator.constructMap();
	Map* nextMap = mapGenerator.getMap();

	mapGenerator.setMapBuilder(loadEditMapBuilder);
	mapGenerator.constructMap();
	Map* editMap = mapGenerator.getMap();

	delete nextLevelMapBuilder;
	delete loadEditMapBuilder;
	delete nextMap;
	delete editMap;
	*/

	MapBuilder* loadEditMapBuilder = new LoadEditedMapBuilder("test.json");
	loadEditMapBuilder->createMap();
	loadEditMapBuilder->configMap();
	loadEditMapBuilder->getMap()->displayMap();
	cout << "good";
	int i;
	cin >> i;

	return 0;
}
