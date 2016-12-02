/*//! @file
//! @brief Header file for the MapTest class
//!
#pragma once
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

using namespace CppUnit;

//! Test Class for the Map class
class MapTest : public CppUnit::TestFixture {
        CPPUNIT_TEST_SUITE(MapTest);
        CPPUNIT_TEST(testMapCellFilled);
        CPPUNIT_TEST(testMapCellEmpty);
        CPPUNIT_TEST(testValidPath);
        CPPUNIT_TEST(testInvalidPath);
        CPPUNIT_TEST(testValidIsBeside);
        CPPUNIT_TEST(testInvalidIsBeside);
        CPPUNIT_TEST_SUITE_END();
public:
        int runTestSuite();
        void setUp();
        void tearDown();
protected:
        void testMapCellFilled();
        void testMapCellEmpty();
        void testValidPath();
        void testInvalidPath();
        void testValidIsBeside();
        void testInvalidIsBeside();
private:
        Map *map;
};

*/