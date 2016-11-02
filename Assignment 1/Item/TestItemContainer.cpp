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
#include "ItemContainer.h"
using namespace CppUnit;
using namespace std;

//! Test Class for the ItemContainer class
//! It must be a subclass of CppUnit::TestFixture
//! It then uses CPPUNIT_TEST_SUITE() to create the test suite, and CPPUNIT_TEST() to include the test methods in the test suite. 
//! CPPUNIT_TEST_SUITE_REGISTRATION() is then used to register the test class in the test registry.
class TestItemContainer : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestItemContainer);
	CPPUNIT_TEST(testAddItem);
	CPPUNIT_TEST(testGetItem);
	CPPUNIT_TEST(testValidItem);
	CPPUNIT_TEST(testInvalidItem);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp(void);
	void tearDown(void);
protected:
	void testAddItem(void);
	void testGetItem(void);
	void testValidItem(void);
	void testInvalidItem();
private:
	ItemContainer *ItemContainerObject;

};

//!Register for running the test
CPPUNIT_TEST_SUITE_REGISTRATION(TestItemContainer);//most important

//! test method to test the AddItem() method of the ItemContainer class 
//! Test Case: the size of the container is increased by one after adding an item to it
void TestItemContainer::testAddItem(void)
{
	Item newItem;
	int OldSize = ItemContainerObject->getItems().size();
	ItemContainerObject->addItem(newItem);
	int NewSize = ItemContainerObject->getItems().size();
	CPPUNIT_ASSERT(OldSize == NewSize - 1);
}

//! test method to test the GetItem() method of the ItemContainer class 
//! Test Case: if we put an item of a certain type in the container,
//! getItem() will return this object
void TestItemContainer::testGetItem(void)
{
	vector<Enhancement> influencesofnewitem= vector<Enhancement>();
	Item newItem("Armor", influencesofnewitem);
	ItemContainerObject->addItem(newItem);
	Item retreivedItem= ItemContainerObject->getItem("Armor");
	CPPUNIT_ASSERT(newItem.getType() == retreivedItem.getType());
	return;
}

//! test method to thest the validateItem() method of the Item class
//! Test Case: calling validateItem() on a valid item should return true 
void TestItemContainer::testValidItem(void)
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
//! Test Case: calling validateItem() on an invalid item should return true 
void TestItemContainer::testInvalidItem(void)
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

//! setUp() method that is executed before all the test cases that the test class includes 
void TestItemContainer::setUp(void)
{
	ItemContainerObject = new ItemContainer();
}

//! tearDown() method that is executed after all the test cases that the test class includes 
void TestItemContainer::tearDown(void)
{
	delete ItemContainerObject;
}
