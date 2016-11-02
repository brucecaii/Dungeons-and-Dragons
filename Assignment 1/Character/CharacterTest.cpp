//! @file 
//! @brief Implementation file for the Character Testing class  
//!

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
using namespace CppUnit;
#include "Character.h"

//! Test Class for the Character class
class CharacterTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(CharacterTest);
	CPPUNIT_TEST(testValidNewCharacter);
	CPPUNIT_TEST(testInvalidNewCharacter);
	CPPUNIT_TEST(testHit);
	CPPUNIT_TEST(testHp);
	CPPUNIT_TEST(testLevelUp);
	CPPUNIT_TEST_SUITE_END();
protected:
	void testValidNewCharacter();
	void testInvalidNewCharacter();
	void testHit();
	void testHp();
	void testLevelUp();
};

//! test case registration
CPPUNIT_TEST_SUITE_REGISTRATION(CharacterTest);

//! test method to test the validateNewCharacter() method of the Character class 
//! Test Case: a valid newly created character should have all its ability scores in the [3-18] range
//! Tested item: Character::validateNewCharacter()
void CharacterTest::testValidNewCharacter()
{
	Character *conan = new Character(12, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter());
}
//! testing to see if hp is correct upon creation

void CharacterTest::testHp()
{
	Character *conan = new Character(12, 12, 12, 12, 12, 12);

	CPPUNIT_ASSERT(conan->getHitPoints() == 22);
}
//! strength should be double upon lvl up.
void CharacterTest::testLevelUp() 
{
Character *conan = new Character(5, 5, 5, 5, 5, 5);
conan->levelUp();
CPPUNIT_ASSERT(conan->getStrength()==10);
}


//! test method to test the validateNewCharacter() method of the Character class 
//! Test Case: an invalid newly created character should have any of its ability scores outside the [3-18] range
//! Tested item: Character::validateNewCharacter()
void CharacterTest::testInvalidNewCharacter()
{
	Character *conan = new Character(20, 12, 12, 12, 12, 12);
	CPPUNIT_ASSERT(conan->validateNewCharacter() == false);
}

//! test method to test the hit() method of the Map class 
//! Test Case: a character that has been hit(x) should have its hit points reduced by x 
//! Tested item: Character::hit()
void CharacterTest::testHit()
{
	Character *conan = new Character(12, 12, 12, 12, 12, 12);
	conan->hit(4);
	CPPUNIT_ASSERT(conan->getHitPoints() == 6);
}

