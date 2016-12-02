//! @file
//! @brief Implementation file for the MapTest class

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
#include "../Map/Map.h"
#include "../Character/Character.h"
#include "../Dice/Dice.h"
#include "../Item/Item.h"


using namespace CppUnit;

//! Test Class for the Map class
class Tests : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(Tests);
	CPPUNIT_TEST(testMapCellFilled);
	CPPUNIT_TEST(testMapCellEmpty);
	CPPUNIT_TEST(testValidPath);
	CPPUNIT_TEST(testInvalidPath);
	CPPUNIT_TEST(testValidIsBeside);
	CPPUNIT_TEST(testInvalidIsBeside);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp();
	void tearDown();
protected:
	//! Tests pertaining to map
	void testMapCellFilled();
	void testMapCellEmpty();
	void testValidPath();
	void testInvalidPath();
    void testValidIsBeside();
    void testInvalidIsBeside();

	//! Tests pertaining to item

	void testValidItem(void);
	void testInvalidItem();
	void testValidEnhancementBonus(void);
	void testInvalidEnhancementBonus();


	//! Tests pertaining to dice 
	void testDiceRollInputValidity();
	void testDiceRollingBounds();
	void testDiceRollOutputValidity();

	//! 
	void testValidNewCharacter();
	void testInvalidNewCharacter();
	void testHit();
	void testHp();
	void testLevelUp();



private:
	Map *map;
};

//! cppunit registry creation
CPPUNIT_TEST_SUITE_REGISTRATION(Tests);

//! method called before every test case in this test class
void Tests::setUp() {
	map = new Map();
}

//! method called after every test case in this test class
void Tests::tearDown() {
	delete map;
}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after filling the cell
//! Tested item: Map::isOccupied()
void Tests::testMapCellFilled() {
	// context: fill a cell
	map->fillCell(1, 1, 'a');
	//test: isOccupied() should return true after the cell having been filled
	CPPUNIT_ASSERT(true == map->isOccupied(1, 1));
}

//! test method to test the isOccupied() method of the Map class
//! Test Case: the returned value should be true after emptying the cell
//! Tested item: Map::isOccupied()
void Tests::testMapCellEmpty() {
	// context: make a cell empty
	map->fillCell(1, 1, ' ');
	// test: isOoccupied() should return false if the cell was not filled
	CPPUNIT_ASSERT(false == map->isOccupied(1, 1));
}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be true if there is a valid path in the map
//! Tested item: Map::validatePath()
void Tests::testValidPath() {
	// context: create a map with a valid path
        map->fillCell(0, 0, 'W');
        map->fillCell(1, 0, 'W');
        map->fillCell(0, 1, 'S');
        map->fillCell(1, 1, 'E');

	// test: validatePath() should return true
	CPPUNIT_ASSERT(true == map->validatePath());
}

//! test method to test the validatePath() method of the Map class
//! Test Case: the returned value should be false if there is no valid path in the map
//! Tested item: Map::validatePath()
void Tests::testInvalidPath() {
	// context: create a map without a valid path
        map->fillCell(0, 0, 'S');
        map->fillCell(2, 2, 'E');

	// test: validatePath() should return false
	CPPUNIT_ASSERT(false == map->validatePath());
}

//! test method to test the isBeside() method of the Map class
//! Test Case: the returned value should be true if there is a specified cell type adjacent to a cell
//! Tested item: Map::isBeside(int x, int y, char type)
void Tests::testValidIsBeside() {
	// context: create a map with a desired type adjacent to a cell
        map->fillCell(0, 0, 'E');

	// test: isBeside(int x, int y, char type) should return true
	CPPUNIT_ASSERT(true == map->isBeside(0, 1, 'E'));
}

//! test method to test the isBeside() method of the Map class
//! Test Case: the returned value should be false if there is not a specified cell type adjacent to a cell
//! Tested item: Map::isBeside(int x, int y, char type)
void Tests::testInvalidIsBeside() {
	// context: create a map with a desired type adjacent to a cell
        // No specific cells required.

	// test: isBeside(int x, int y, char type) should return true
	CPPUNIT_ASSERT(false == map->isBeside(0, 1, 'E'));
}



//! items
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



//! dice 

//! test method for role function of the Dice class 
//! Test Case: the the validity of input string
void DiceTest::testDiceRollInputValidity()
{
	int result = 0;

	// test that if the string is valid, the result is calculated
	result = Dice::roll("4d20");
	CPPUNIT_ASSERT(result > 0);
	result = Dice::roll("3d10+1");
	CPPUNIT_ASSERT(result > 0);

	// test that is the string is invalid, roll() returns -1
	result = Dice::roll("4d");
	CPPUNIT_ASSERT(result == -1);
	result = Dice::roll("d20");
	CPPUNIT_ASSERT(result == -1);
	result = Dice::roll("420");
	CPPUNIT_ASSERT(result == -1);
	result = Dice::roll("4d20+");
	CPPUNIT_ASSERT(result == -1);
}

//! test method for role function of the Dice class 
//! Test Case: the the validity of output number
void DiceTest::testDiceRollOutputValidity()
{
	int result[5];
	int sec = (int)time(NULL);
	for (int i = 0; i < 5; i++) {
		while ((int)time(NULL) == sec) {}
		sec = (int)time(NULL);
		result[i] = Dice::roll("4d20");
	}
	CPPUNIT_ASSERT(!(result[0] == result[1] == result[2] == result[3] == result[4]));
}


//! test method for role function of the Dice class 
//! Test Case: the upperbound of all values returned from roll function
void DiceTest::testDiceRollingBounds()
{
	int result = 0;

	for (int j = 1; j <= 1000; j++) {
		result = Dice::roll("1d4");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 4);
	}
	for (int j = 1; j <= 1000; j++) {
		result = Dice::roll("1d6");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 6);
	}
	for (int j = 1; j <= 1000; j++) {
		int numbers = Dice::roll("1d8");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 8);
	}
	for (int j = 1; j <= 1000; j++) {
		int numbers = Dice::roll("1d10");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 10);
	}
	for (int j = 1; j <= 1000; j++) {
		int numbers = Dice::roll("1d12");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 12);
	}
	for (int j = 1; j <= 1000; j++) {
		int numbers = Dice::roll("1d20");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 20);
	}
	for (int j = 1; j <= 1000; j++) {
		int numbers = Dice::roll("1d100");
		CPPUNIT_ASSERT(result >= 1);
		CPPUNIT_ASSERT(result <= 100);
	}
}


//! character 


void CharacterTest::testValidNewCharacter()
{
	CharacterAttr characterAttr(3, 3, 3, 3, 3, 3);
	Character *bruce = new Character(&characterAttr);
	CPPUNIT_ASSERT(bruce->validateNewCharacter());
}
//! testing to see if hp is correct upon creation

void CharacterTest::testHp()
{
	CharacterAttr characterAttr(1, 1, 1, 1, 1, 1);
	Character *bruce = new Character(&characterAttr);

	CPPUNIT_ASSERT(bruce->getHitPoints() == 22);
}
//! strength should be double upon lvl up.
void CharacterTest::testLevelUp()
{
	CharacterAttr characterAttr(3, 3, 3, 3, 3, 3);
	Character *bruce = new Character(&characterAttr);
	bruce->setLevel(1);
	bruce->levelUp();
	CPPUNIT_ASSERT(bruce->getLevel() == 2);
}


//! test method to test the validateNewCharacter() method of the Character class 
//! Test Case: an invalid newly created character should have any of its ability scores outside the [3-18] range
//! Tested item: Character::validateNewCharacter()
void CharacterTest::testInvalidNewCharacter()
{
	CharacterAttr characterAttr(3, 3, 3, 3, 3, 3);
	Character *bruce = new Character(&characterAttr);
	CPPUNIT_ASSERT(bruce->validateNewCharacter() == false);
}

//! test method to test the hit() method of the Map class 
//! Test Case: a character that has been hit(x) should have its hit points reduced by x 
//! Tested item: Character::hit()
void CharacterTest::testHit()
{
/*	CharacterAttr characterAttr(3, 3, 3, 3, 3, 3);
	Character *bruce = new Fighter(&characterAttr);
	CharacterAttr characterAttr(3, 3, 3, 3, 3, 3);
	Character *enemy = new Fighter(&characterAttr);
	enemy->attack(bruce);
	CPPUNIT_ASSERT(bruce->getHitPoints() == 6);
	*/
}

