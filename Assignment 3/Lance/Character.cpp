//! @file
//! @brief Implementation file for the Character class

#include "Character.h"
#include "Strategy.h"
#include <cmath>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

//! Constructor: passes values to each ability score, set hit points to 10, assigns a Strategy type and a map position.
Character::Character(int str, int dex, int con, int intel, int wis, int cha, Strategy* initStrategy, int posX, int posY, char typeOnMap) {
	modifers[0] = modifier(str);
	modifers[1] = modifier(dex);
	modifers[2] = modifier(con);
	modifers[3] = modifier(intel);
	modifers[4] = modifier(wis);
	modifers[5] = modifier(cha);

	abilityScores[0] = str; abilityScoresFromChar[0] = str;
	abilityScores[1] = dex; abilityScoresFromChar[1] = dex;
	abilityScores[2] = con; abilityScoresFromChar[2] = con;
	abilityScores[3] = intel; abilityScoresFromChar[3] = intel;
	abilityScores[4] = wis; abilityScoresFromChar[4] = wis;
	abilityScores[5] = cha; abilityScoresFromChar[5] = cha;

	currentHitPoints = 10 + abilityScores[2];
	armorclass = 10 + modifers[1];
        ArmorfromChar  = 10 + modifers[1];

	attackbonus  = (modifers[0] + modifers[1])*lvl;
        attackbonusFromChar = (modifers[0] + modifers[1])*lvl;
	damagebonus = modifers[0];

        this->strategy = initStrategy;
        this->typeOnMap = typeOnMap;
        currentPosition.resize(2);
        currentPosition[0] = posX;
        currentPosition[1] = posY;
}

//! Getter for the Strength ability
//! @return int representing the Strength ability
int Character::getStrength() {
	return abilityScores[0];
}

//! Getter for the Dexterity ability
//! @return int representing the Dexterity ability
int Character::getDexterity() {
	return abilityScores[1];
}

//! Getter for the Constitution ability
//! @return int representing the Constitution ability
int Character::getConstitution() {
	return abilityScores[2];
}

//! Getter for the Intelligence ability
//! @return int representing the Intelligence ability
int Character::getIntelligence() {
	return abilityScores[3];
}

//! Getter for the Wisdom ability
//! @return int representing the Wisdom ability
int Character::getWisdom() {
	return abilityScores[4];
}

//! Getter for the Charisma ability
//! @return int representing the Charisma ability
int Character::getCharisma() {
	return abilityScores[5];
}


//! Getter for the current character level
//! @return int representing the current character level
int Character::getLevel() {
	return lvl;
}

//! getters for base scores used for saving
int Character::getStrengthFromBase() {
	return abilityScoresFromChar[0];
}

int Character::getDexterityFromBase() {
	return abilityScoresFromChar[1];
}

int Character::getConstitutionFromBase() {
	return abilityScoresFromChar[2];
}

int Character::getIntelligenceFromBase() {
	return abilityScoresFromChar[3];
}

int Character::getWisdomFromBase() {
	return abilityScoresFromChar[4];
}

int Character::getCharismaFromBase() {
	return abilityScoresFromChar[5];
}


//! setters for Base abilityscores
void Character::setStrength(int i) {
	abilityScoresFromChar[0] = i;
}

void Character::setDexterity(int i) {
	abilityScoresFromChar[1] = i;
}

void Character::setConstitution(int i) {
	abilityScoresFromChar[2] = i;
}

void Character::setIntelligence(int i) {
	abilityScoresFromChar[3] = i;
}

void Character::setWisdom(int i) {
	abilityScoresFromChar[4] = i;
}

void Character::setCharisma(int i) {
	abilityScoresFromChar[5] = i;
}

//! this method is when you wish to level up the character and it scales the abilties appropiatly.
void Character::levelUp() {
	this->lvl++;
	for (int i = 0; i < 5; i++) {
		abilityScores[i] = abilityScores[i] * lvl;
	}
	this->currentHitPoints *= lvl;
}

//! according to d20 rules modifier is (ability score -10) /2
//! @param int representing score of one of the abilities
//! @param int representing updated ability score after modifer was applied
int Character::modifier(int abilityscore) {
	int modi = floor((abilityscore - 10) / 2);
	if (modi <= 0) {
		return 0;
	}
	return modi;
}

//! Getter for the number of character's hitpoints
//! @return int: value of currentHitPoints
int Character::getHitPoints() {
	return currentHitPoints;
}

//! Setter for the number of character's hitpoints
//! @param int value of currentHitPoints
void Character::setHitPoints(int HP) {
  this->currentHitPoints = HP;
}

//! Utility method to display lots of information about the current character
void Character::displayCharacter() {
	cout << "*******************************************" << endl;
	cout << "Here are you stats for your character " << typeOnMap << endl;
	cout << "Your strength is : " << abilityScores[0] << endl;
	cout << "Your dexterity is : " << abilityScores[1] << endl;
	cout << "Your constitution is : " << abilityScores[2] << endl;
	cout << "Your intelligence is : " << abilityScores[3] << endl;
	cout << "Your wisdom is : " << abilityScores[4] << endl;
	cout << "Your charisma is : " << abilityScores[5] << endl;
	cout << "Your hp is : " << this->getHitPoints() << endl;
	cout << "Your level is : " << this->getLevel() << endl;
	cout << "Your armorclass is : " << armorclass << endl;
	cout << "Your attackbonus is : " << attackbonus << endl;
	cout << "Your position is : (" << currentPosition[0] << "," << currentPosition[1]<< ")" << endl;
	cout << "*******************************************" << endl;
	cout << endl;
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

//! Implementation of the setCurrentPosition method. Searches in the map for a start cell, and if found, assigns it to the Character's position on the map.
//! @param a Map object to iterate through
//! @return bool value, true of the character is valid (stats should be in the 3-18 range for a new character), false if invalid.
bool Character::setCurrentPosition(Map m) {
  // Assumption that there is only one user playing (at most 1 'S').
  for(int i = 0; i < m.getMapWidth(); i++) {
    for(int j = 0; j < m.getMapLength(); j++) {
      if (m.getCell(i, j) == 'S') {
        currentPosition[0] = i;
        currentPosition[1] = j;
        return true;
      }
    }
  }
  cout << "Currently no start cell!" << endl;
  return false;
}

//! Setter for a new strategy
//! @param pointer to a new strategy
void Character::setStrategy(Strategy* newStrategy) {
  delete this->strategy;
  this->strategy = newStrategy;
}

//! Implementation of the executeStrategy method. Calls the current strategy's execute method, and passes along a reference to the current character object.
//! @param Reference to the current map object
//! @param Reference to the current character object
void Character::executeStrategy(Map& m) {
  this->strategy->execute(m, *this);
}

//! Getter for current character's x-coordinate in the current map.
//! @return int representnt current chaacter x-coordinate
int Character::getCurrentPositionX() {
  return this->currentPosition[0];
}

//! Getter for current character's y-coordinate in the current map.
//! @return int representnt current chaacter y-coordinate
int Character::getCurrentPositionY() {
  return this->currentPosition[1];
}

//! Setter for current character's x-coordinate in the current map.
//! @param int representnt current character x-coordinate
void Character::setCurrentPositionX(int charPosX) {
  this->currentPosition[0] = charPosX;
}

//! Setter for current character's y-coordinate in the current map.
//! @param int representnt current character y-coordinate
void Character::setCurrentPositionY(int charPosY) {
  this->currentPosition[1] = charPosY;
}

//! Getter for current character's type as represented on the current map
//! @return a char representing the type of character as seen on the map
char Character::getTypeOnMap() {
  return this->typeOnMap;
}

//! Setter for current character's type as represented on the current map
//! @param a char representing the type of character as seen on the map
void Character::setTypeOnMap(char t) {
  this->typeOnMap = t;
}
