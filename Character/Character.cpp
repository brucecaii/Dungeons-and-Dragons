
#include "Character.h"
#include <cmath>
#include <iostream>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>


using namespace std;


//! ok so in this file you have the method defintions for character and fighter which inherits from character
//! further to this, the main is in this cpp file. There are two mains and one is always commented out. One is to show that a character is created blah blah blah
//! the other is for testing. if you want to switch from character display to testing just comment out one main and run the program with the other. 



Fighter::Fighter() {  //! default construtor
}

Character::Character() { //! default constutor
}


//! Constructor: passes values to each ability score and set hit points to 10
Character::Character(int str, int dex, int con, int intel, int wis, int cha)
{

	modifers[0] = modifier(str);
	modifers[1] = modifier(dex);
	modifers[2] = modifier(con);
	modifers[3] = modifier(intel);
	modifers[4] = modifier(wis);
	modifers[5] = modifier(cha);


	abilityScores[0] = str;
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	//! and set hit points to 10 and multyping it by consitution level, as consitution level influnces hitpoints and by lvl

	currentHitPoints = 10 + abilityScores[2];
	armorclass = 10+ modifers[1];
	attackbonus = (modifers[0] + modifers[1])*lvl;
	damagebonus = modifers[0];


}


//! this method is when you wish to level up the character and it scales the abilties appropiatly. 
void Character::levelUp() {  
	this->lvl++;
	for (int i = 0; i < 5; i++) {
		abilityScores[i] = abilityScores[i] * lvl;

	}
	this->currentHitPoints *=lvl;

}

//!according to rules modifier is (ability score -10) /2
int Character::modifier(int abilityscore) { 
	int modi = floor((abilityscore - 10) / 2);
	if (modi <= 0) {
		return 0;
	}
	return modi;
}


//! Implementation of the verification of a newly created Character
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid. 
bool Character::validateNewCharacter()
{
	for (int i = 0; i <= 5; i++)
		if (abilityScores[i]<3 || abilityScores[i]>18)
			return false;
	return true;
}

//! Implementation of fill cell, set any cell to anything it might eventually contain
//! @param damage: damage sustained by the character
void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;  // this forumla will probaly change in next assigment due to adding mitigation from amor class
}

//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}
//! ok this is how you will create a fighter class and a figher , for now its the same as character but in the project when its integrated more with games there will be some special perks to being a fighter
Fighter::Fighter(int str, int dex, int con, int intel, int wis, int cha) : Character(str, dex ,con, intel, wis, cha)

{ 


 


}


void Character::showAbilityScores() {
	for (int i = 0; i < 6; i++) {
		cout << abilityScores[i] << endl;

	}
}

int Character::getStrength() {
	return abilityScores[0];
}




//! the main

int main()
{

	srand(time(0)); //! this is used for randomizing our inputs
	cout << "HI HOPE U ARE DOING SWELL TODAY GOOD SIR, WELCOME TO CHARACTER CREATION OF DUNGEONS AND DRAGONS COMP345 VERSION, GET READY TO HAVE FUN FUN FUN! " << endl;
	Fighter fight;
		cout << "We will now generate a character of class fighter with random ability score inputs" << endl;
	int values[6]; //! put random values in here than put values in constructor of fighter.

	for (int i = 0; i < 6; i++) {
		int max = 10;
		int min = 3;
		int randNum = rand() % (max - min + 1) + min;
		values[i] = randNum;

	}
	srand(time(0));

	fight = Fighter(values[0], values[1], values[2], values[3], values[4], values[5]);
	
	
	//Fighter fight = Fighter(10, 10, 10, 10, 10, 10);
	cout << "the hit points is " << fight.getHitPoints() << endl;
	cout << "the respective ability scores are "<< endl;
	fight.showAbilityScores();

	
	
	





	
	return 0;

}





//! main() function. Entry point of the program
//! It does the following: 
//! 1. Create a test suite object from the registry as populated by the code in the Test Classes
//! 2. Create a test runner that will execute all the tests in the registry
//! 3. (optionally) sets an outputter that will output the results
//! 4. Run the test cases. 
/*
int main(int argc, char* argv[])
{
	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(suite);

	// Change the default outputter to a compiler error format outputter
	runner.setOutputter(new CppUnit::CompilerOutputter(&runner.result(),
		std::cerr));
	// Run the tests.
	bool wasSucessful = runner.run();

	getchar();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}
*/