//! @file 
//! @brief Implementation file for the Character class  
//!

#include "Character.h"

//! Constructor: passes values to each ability score and set hit points to 10
Character::Character(int str, int dex, int con, int intel, int wis, int cha)
{
	abilityScores[0] = str; 
	abilityScores[1] = dex;
	abilityScores[2] = con;
	abilityScores[3] = intel;
	abilityScores[4] = wis;
	abilityScores[5] = cha;

	// and set hit points to 10
	currentHitPoints = 10;
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
	currentHitPoints = currentHitPoints - damage; 
}

//! Implementation of a getter method for currentHitPoints
//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints; 
}
