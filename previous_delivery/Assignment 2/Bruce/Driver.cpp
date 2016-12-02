//! @file 
//! @brief Driver file to create and execute the test suite 
//!
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>
#include "MapGenerator.h"
using namespace std;
int runUnitTest();

/*
! Main Driver
*/
int main() {
	//! Run the unit test
	int test = runUnitTest();
	test == 0 ? (cout << "Unit tests passed." << endl << endl) : (cout << "Unit tests failed." << endl << endl);
	cout << "------------------------------------------------------------" << endl << endl;
	//! Create director and builders
	MapGenerator mapGenerator;
	MapBuilder* nextLevelMapBuilder = new NextMapBuilder("nextMap.json");
	MapBuilder* loadEditMapBuilder = new LoadEditedMapBuilder("savedMap.json");
	//! Assign next map (in game) builder to director and construct the map
	mapGenerator.setMapBuilder(nextLevelMapBuilder);
	mapGenerator.constructMap();
	cout << "This is to demo next dungeons builder." << endl << "Here is the map generated" << endl;
	mapGenerator.getMap()->displayMap();
	cout << "------------------------------------------------------------" << endl << endl;
	//! Assign saved map (map editor) builder to director and construct the map
	mapGenerator.setMapBuilder(loadEditMapBuilder);
	mapGenerator.constructMap();
	cout << "This is to demo saved edited map builder." << endl << "Here is the saved edited map generated" << endl;
	mapGenerator.getMap()->displayMap();
	cout << "As you can see the map is not finished editing yet." << endl << endl;
	cout << "------------------------------------------------------------" << endl ;
	//! Delete memories
	delete nextLevelMapBuilder;
	delete loadEditMapBuilder;
	//! Prompt close console
	int i = 1;
	while (i == 1) {
		cout << endl << "Enter 0 to quit the program." << endl;
		cin >> i;
	}
	return 0;
}

/*
! Run Unit Test Helper
*/
int runUnitTest() {
	//! Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
	//! Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);
	//! Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	//! Run the tests.
	bool wasSucessful = runner.run();
	cout << "------------------------------------------------------------" << endl;
	cout << endl << "Press enter two times to continue" << endl;
	getchar();
	//! Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}