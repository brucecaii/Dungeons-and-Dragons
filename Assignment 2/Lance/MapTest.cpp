//! @file
//! @brief Implementation file for the MapTest class

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "Map.h"
#include "MapTest.h"

using namespace CppUnit;


//! cppunit registry creation
//CPPUNIT_TEST_SUITE_REGISTRATION(MapTest);

//int MapTest::runTestSuite() {
        // Get the top level suite from the registry
        //CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

        // Adds the test to the list of test to run
        //CppUnit::TextUi::TestRunner runner;
        //runner.addTest( suite );

        // Change the default outputter to a compiler error format outputter
        //runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                             //std::cerr ) );
        // Run the tests.
        //bool wasSucessful = runner.run();

        //getchar();

        // Return error code 1 if the one of test failed.
        //return wasSucessful ? 0 : 1;

//}
//! method called before every test case in this test class
//void MapTest::setUp() {
	//map = new Map();
//}

//! method called after every test case in this test class
//void MapTest::tearDown() {
	//delete map;
//}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after filling the cell
//! Tested item: Map::isOccupied()
//void MapTest::testMapCellFilled() {
	// context: fill a cell
	//map->fillCell(1, 1, 'a');
	//test: isOccupied() should return true after the cell having been filled
	//CPPUNIT_ASSERT(true == map->isOccupied(1, 1));
//}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after emptying the cell
//! Tested item: Map::isOccupied()
//void MapTest::testMapCellEmpty() {
	// context: make a cell empty
	//map->fillCell(1, 1, ' ');
	// test: isOoccupied() should return false if the cell was not inline 	CPPUNIT_ASSERT(false == map->isOccupied(1, 1));
//}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: Map::validatePath()
//void MapTest::testValidPath() {
	// context: create a map with a valid path
        //map->fillCell(0, 0, 'W');
        //map->fillCell(1, 0, 'W');
        //map->fillCell(0, 1, 'S');
        //map->fillCell(1, 1, 'E');

	// test: validatePath() should return true
	//CPPUNIT_ASSERT(true == map->validatePath());
//}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be false if there is no valid path in the map
//! Tested item: Map::validatePath()
//void MapTest::testInvalidPath() {
	// context: create a map without a valid path
        //map->fillCell(0, 0, 'S');
        //map->fillCell(2, 2, 'E');

	// test: validatePath() should return false
	//CPPUNIT_ASSERT(false == map->validatePath());
//}

//! test method to test the isBeside() method of the Map class
//! Test Case: the returned value should be true if there is a specified cell type adjacent to a cell
//! Tested item: Map::isBeside(int x, int y, char type)
//void MapTest::testValidIsBeside() {
	// context: create a map with a desired type adjacent to a cell
        //map->fillCell(0, 0, 'E');

	// test: isBeside(int x, int y, char type) should return true
	//CPPUNIT_ASSERT(true == map->isBeside(0, 1, 'E'));
//}

//! test method to test the isBeside() method of the Map class
//! Test Case: the returned value should be false if there is not a specified cell type adjacent to a cell
//! Tested item: Map::isBeside(int x, int y, char type)
//void MapTest::testInvalidIsBeside() {
	// context: create a map with a desired type adjacent to a cell
        // No specific cells required.

	// test: isBeside(int x, int y, char type) should return true
	//CPPUNIT_ASSERT(false == map->isBeside(0, 1, 'E'));
//}

