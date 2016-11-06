#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>
#include "MapGenerator.h"
using namespace std;

int main() {

	MapGenerator mapGenerator;
	MapBuilder* nextLevelMapBuilder = new NextMapBuilder("nextMap.json");
	MapBuilder* loadEditMapBuilder = new LoadEditedMapBuilder("savedMap.json");
	
	mapGenerator.setMapBuilder(nextLevelMapBuilder);
	mapGenerator.constructMap();
	Map* nextMap = mapGenerator.getMap();
	cout << "This is to demo next dungeons builder." << endl << "Here is the map generated" << endl;
	nextMap->displayMap();

	cout << "------------------------------------------------------------" << endl << endl;

	mapGenerator.setMapBuilder(loadEditMapBuilder);
	mapGenerator.constructMap();
	Map* editMap = mapGenerator.getMap();
	cout << "This is to demo saved edited map builder." << endl << "Here is the saved edited map generated" << endl;
	editMap->displayMap();
	cout << "As you can see the map is not finished editing yet." << endl;

	delete nextLevelMapBuilder;
	delete loadEditMapBuilder;
	delete nextMap;
	delete editMap;

	int i = 1;
	while (i == 1) {
		cout << endl << "Enter 0 to quit the program.";
		cin >> i;
	}

	return 0;
}
