//! @file 
//! @brief File containing the Test Class and the Test Methods
//!

#include <iostream>
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
#include "Item.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItem : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItem);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST(testValidEnhancementBonus);
	CPPUNIT_TEST(testInvalidEnhancementBonus);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidItem(void);
	void testInvalidItem();
	void testValidEnhancementBonus(void);
	void testInvalidEnhancementBonus();
};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItem);//most important

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItem::testValidItem(void)
{
	//Vector of enhancements
	vector<Enhancement> helmet_enhan;

	//Creating all the types of enhancements
	Enhancement intelligence("Intelligence", 5);
	Enhancement wisdom("Wisdom", 5);
	Enhancement armor("Armor class", 5);

	//Adding helmet allowed enhancements to vector
	helmet_enhan.push_back(intelligence);
	helmet_enhan.push_back(wisdom);
	helmet_enhan.push_back(armor);
	
	Item helmet("Helmet", helmet_enhan);
	
	CPPUNIT_ASSERT(helmet.validateItem() == true);
}

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on an invalid item should return false 
void TestItem::testInvalidItem(void)
{
	//Vector of enhancements
	vector<Enhancement> helmet_enhan;

	//Creating all the types of enhancements
	Enhancement intelligence("Intelligence", 5);
	Enhancement wisdom("Wisdom", 5);
	Enhancement armor("Armor class", 5);
	Enhancement fake("Fake enhancement", 5);

	//Adding helmet allowed enhancements to vector
	helmet_enhan.push_back(intelligence);
	helmet_enhan.push_back(wisdom);
	helmet_enhan.push_back(armor);
	helmet_enhan.push_back(fake);

	Item helmet("Helmet", helmet_enhan);

	CPPUNIT_ASSERT(helmet.validateItem() == false);
}

//! test method to test the validateBonus() method of the Enhancement class
//! Test Case: calling validateBonus() on an valid item should return true 
void TestItem::testValidEnhancementBonus(void)
{
	//Creating all the types of enhancements
	Enhancement intelligence("Intelligence", 5);
	CPPUNIT_ASSERT(intelligence.validateBonus() == true);
}

//! test method to thest the validateBonus() method of the Item class
//! Test Case: calling validateBonus() on an invalid item should return false
void TestItem::testInvalidEnhancementBonus(void)
{
	//Creating all the types of enhancements
	Enhancement intelligence("Intelligence", 10);
	CPPUNIT_ASSERT(intelligence.validateBonus() == false);
}