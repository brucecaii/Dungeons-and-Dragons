//! @file 
//! @brief Driver file to create and execute the test suite 
//!
//! Brief instruction on how to set CppUnit:
//! from: http ://www.comp.nus.edu.sg/~cs3215/tools/cppunitAll.html
//!
//!	First, to install cppUnit :
//!
//!	 1. Unpack the CppUnit archive (https://sourceforge.net/projects/cppunit/files/cppunit/1.12.1/) to a directory of your choice, in this example I assume it is D:\. 
//!  2. Go to D:/cppunit-1.12.1/src and open the CppUnitLibraries.dsw in Visual Studio.
//!  3. Select the cppunit project in the Solution Explorer and go to 'Project > Properties > Configuration Properties > Librarian > General. Put "Debug\cppunit.lib" in the ‘Output File’ textbox. 
//!  4. Right-click on the cppunit project in the Solution Explorer pane and choose Build.
//!  5. After successful compilation, D:/cppunit-1.12.1/lib/cppunit.lib is produced which you then need to setup the Visual Studio Linker with (see below).

//!
//! To setup a project from scratch for Compilation / Linking:
//!
//!	  1. Activate 'Project > Properties > C/C++ >  Code Generation > Runtime Library > Multi - threaded Debug DLL'
//!	  2. Go to 'Project > Properties > C/C++ > General'. Put "D:\cppunit-1.12.1\include" in the 'Additional Include Directories' text box.
//!	  3. Go to 'Project > Properties > Linker > Input'. Put "D:\cppunit-1.12.1\lib\cppunit.lib" in the 'Additional Dependences' text box.
//!	  4. Go to 'Project > Properties > Build Events > Post-Build Event'. Put '"$(TargetPath)"' in the 'Command Line' textbox.Put 'Unit Tests...' in the 'Description' textbox.

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "Enhancement.h"
#include "Item.h"

//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
int main(int argc, char* argv[])
{
  // Get the top level suite from the registry
  CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

  // Adds the test to the list of test to run
  CppUnit::TextUi::TestRunner runner;
  runner.addTest( suite );

  // Change the default outputter to a compiler error format outputter
  runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                       std::cerr ) );
  // Run the tests.
  bool wasSucessful = runner.run();

  getchar();

  // My Driver
  //Creating all the types of enhancements
  Enhancement intelligence("Intelligence", 5);
  Enhancement wisdom("Wisdom", 5);
  Enhancement armor("Armor class", 5);
  Enhancement strength("Strength", 5);
  Enhancement constitution("Constitution", 5);
  Enhancement charisma("Charisma", 5);
  Enhancement dexterity("Dexterity", 5);
  Enhancement attack("Attack bonus", 5);
  Enhancement damage("Damage bonus", 5);
  Enhancement fake("Fake Enhancement", 5);

  //Adding helmet allowed enhancements to vector
  vector<Enhancement> helmet_enhan;
  helmet_enhan.push_back(intelligence);
  helmet_enhan.push_back(wisdom);
  helmet_enhan.push_back(armor);

  //Adding armor allowed enhancements to vector
  vector<Enhancement> armor_enhan;
  armor_enhan.push_back(armor);

  //Adding shield allowed enhancements to vector
  vector<Enhancement> shield_enhan;
  shield_enhan.push_back(armor);

  //Adding ring allowed enhancements to vector
  vector<Enhancement> ring_enhan;
  ring_enhan.push_back(armor);
  ring_enhan.push_back(strength);
  ring_enhan.push_back(constitution);
  ring_enhan.push_back(wisdom);
  ring_enhan.push_back(armor);

  //Adding belt allowed enhancements to vector
  vector<Enhancement> belt_enhan;
  belt_enhan.push_back(constitution);
  belt_enhan.push_back(strength);

  //Adding boots allowed enhancements to vector
  vector<Enhancement> boots_enhan;
  boots_enhan.push_back(armor);
  boots_enhan.push_back(dexterity);

  //Adding weapon allowed enhancements to vector
  vector<Enhancement> weapon_enhan;
  weapon_enhan.push_back(attack);
  weapon_enhan.push_back(damage);

  // Creates an object with invalid type (unallowed), it will exit with code 1.
  // cout << "-----Creating item with invalid item type-----" << endl;
  // Item invalid_item("Spear", helmet_enhan);

  //Creating valid items and verifying their validity based on game rules (allowed enhancements for each individual item type)
  cout << "//-----------------------------------------------------------------" << endl;
  cout << "//     Creating item of each type and verifying their validity" << endl;
  cout << "//-----------------------------------------------------------------" << "\n" << endl;

  //Creating a helmet object and assigning valid enhancements
  Item helmet_item("Helmet", helmet_enhan);
  cout << "Helmet created with enhancements (+5 Intelligence, +5 Wisdom, +5 Armor class)" << endl;
  cout << "IsItemValid: " << helmet_item.validateItem() << "\n" << endl;

  //Creating a armor object and assigning valid enhancements
  Item armor_item("Armor", armor_enhan);
  cout << "Armor created with enhancements (+5 Armor class)" << endl;
  cout << "IsItemValid: " << armor_item.validateItem() << "\n" << endl;

  //Creating a shield object and assigning valid enhancements
  Item shield_item("Shield", shield_enhan);
  cout << "Shield created with enhancements (+5 Armor class)" << endl;
  cout << "IsItemValid: " << shield_item.validateItem() << "\n" << endl;

  //Creating a ring object and assigning valid enhancements
  Item ring_item("Ring", ring_enhan);
  cout << "Ring created with enhancements (+5 Armor class, +5 Strength, +5 Constitution, +5 Wisdom, +5 Charisma)" << endl;
  cout << "IsItemValid: " << ring_item.validateItem() << "\n" << endl;

  //Creating a belt object and assigning valid enhancements
  Item belt_item("Belt", belt_enhan);
  cout << "Belt created with enhancements (+5 Constitution, +5 Strength)" << endl;
  cout << "IsItemValid: " << belt_item.validateItem() << "\n" << endl;

  //Creating a boots object and assigning valid enhancements
  Item boots_item("Boots", boots_enhan);
  cout << "Boots created with enhancements (+5 Armor class, +5 Dexterity)" << endl;
  cout << "IsItemValid: " << boots_item.validateItem() << "\n" << endl;

  //Creating a helmet object and assigning valid enhancements
  Item weapon_item("Weapon", weapon_enhan);
  cout << "Weapon created with enhancements (+5 Attack bonus, +5 Damage bonus)" << endl;
  cout << "IsItemValid: " << weapon_item.validateItem() << "\n" << endl;

  //Adding invalid enhancement types to enhancement vector of each type
  helmet_enhan.push_back(fake);
  armor_enhan.push_back(fake);
  shield_enhan.push_back(fake);
  ring_enhan.push_back(fake);
  belt_enhan.push_back(fake);
  boots_enhan.push_back(fake);
  weapon_enhan.push_back(fake);

  cout << endl;
  cout << "//-------------------------------------------------------------------------------------------------------" << endl;
  cout << "//     Creating item of each type (with invalid enhancement based on type) and verifying their validity" << endl;
  cout << "//-------------------------------------------------------------------------------------------------------" << "\n" << endl;

  // Adding an unallowed enhancement to each of these item types and checking their validity again
  Item fhelmet_item("Helmet", helmet_enhan);
  cout << "Helmet created with enhancements (+5 Fake Enhancement, +5 Intelligence, +5 Wisdom, +5 Armor class)" << endl;
  cout << "IsItemValid: " << fhelmet_item.validateItem() << "\n" << endl;

  //Creating a armor object and assigning valid enhancements
  Item farmor_item("Armor", armor_enhan);
  cout << "Armor created with enhancements (+5 Fake Enhancement, +5 Armor class)" << endl;
  cout << "IsItemValid: " << farmor_item.validateItem() << "\n" << endl;

  //Creating a shield object and assigning valid enhancements
  Item fshield_item("Shield", shield_enhan);
  cout << "Shield created with enhancements (+5 Fake Enhancement, +5 Armor class)" << endl;
  cout << "IsItemValid: " << fshield_item.validateItem() << "\n" << endl;

  //Creating a ring object and assigning valid enhancements
  Item fring_item("Ring", ring_enhan);
  cout << "Ring created with enhancements (+5 Fake Enhancement, +5 Armor class, +5 Strength, +5 Constitution, +5 Wisdom, +5 Charisma)" << endl;
  cout << "IsItemValid: " << fring_item.validateItem() << "\n" << endl;

  //Creating a belt object and assigning valid enhancements
  Item fbelt_item("Belt", belt_enhan);
  cout << "Belt created with enhancements (+5 Fake Enhancement, +5 Constitution, +5 Strength)" << endl;
  cout << "IsItemValid: " << fbelt_item.validateItem() << "\n" << endl;

  //Creating a boots object and assigning valid enhancements
  Item fboots_item("Boots", boots_enhan);
  cout << "Boots created with enhancements (+5 Fake Enhancement, +5 Armor class, +5 Dexterity)" << endl;
  cout << "IsItemValid: " << fboots_item.validateItem() << "\n" << endl;

  //Creating a helmet object and assigning valid enhancements
  Item fweapon_item("Weapon", weapon_enhan);
  cout << "Weapon created with enhancements (+5 Fake Enhancement, +5 Attack bonus, +5 Damage bonus)" << endl;
  cout << "IsItemValid: " << fweapon_item.validateItem() << "\n" << endl;

  int x;
  cin >> x;


  // Return error code 1 if the one of test failed.
  return wasSucessful ? 0 : 1;
}