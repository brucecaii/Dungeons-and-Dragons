
#include "Character.h"
#include <cmath>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

//! Constructor: passes values to each ability score and set hit points to 10
Character::Character(int str, int dex, int con, int intel, int wis, int cha, Strategy* initStrategy, int posX, int posY, char typeOnMap) {
	//! your modifer values are stored here
	modifers[0] = modifier(str);
	modifers[1] = modifier(dex);
	modifers[2] = modifier(con);
	modifers[3] = modifier(intel);
	modifers[4] = modifier(wis);
	modifers[5] = modifier(cha);

	//! intializing your total scores and base scores , will be same value on constuctor call
	abilityScores[0] = str; abilityScoresFromChar[0] = str;
	abilityScores[1] = dex; abilityScoresFromChar[1] = dex;
	abilityScores[2] = con; abilityScoresFromChar[2] = con;
	abilityScores[3] = intel; abilityScoresFromChar[3] = intel;
	abilityScores[4] = wis; abilityScoresFromChar[4] = wis;
	abilityScores[5] = cha; abilityScoresFromChar[5] = cha;

	//! set hit points to 10 and multyping it by consitution level, as consitution level influnces hitpoints and by lvl
	currentHitPoints = 10 + abilityScores[2];
	//!  base armor class is 10+ the modifer of your dexterity
	armorclass = 10 + modifers[1];
        ArmorfromChar  = 10 + modifers[1];

	//! base attack bonus is your strength and dexterity modifers summed and multiplyed by level
	attackbonus  = (modifers[0] + modifers[1])*lvl;
        attackbonusFromChar = (modifers[0] + modifers[1])*lvl;
	damagebonus = modifers[0];

        this->strategy = initStrategy;
        this->typeOnMap = typeOnMap;
        // Setting position on map
        currentPosition.resize(2);
        currentPosition[0] = posX;
        currentPosition[1] = posY;
}

//! getters below for total abilityscores
int Character::getStrength() {
	return abilityScores[0];
}

int Character::getDexterity() {
	return abilityScores[1];
}

int Character::getConstitution() {
	return abilityScores[2];
}

int Character::getIntelligence() {
	return abilityScores[3];
}

int Character::getWisdom() {
	return abilityScores[4];
}

int Character::getCharisma() {
	return abilityScores[5];
}


//! getter for current level
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
	//updatestats();
}

//! according to rules modifier is (ability score -10) /2
int Character::modifier(int abilityscore) {
	int modi = floor((abilityscore - 10) / 2);
	if (modi <= 0) {
		return 0;
	}
	return modi;
}

//! @param damage: damage sustained by the character
void Character::hit(int damage) {
	currentHitPoints = currentHitPoints - damage;
	//Notify();
}


//! @return int: value of currentHitPoints
int Character::getHitPoints() {
	return currentHitPoints;
}


//! this displays the ability scores
void Character::showAbilityScores() {
	for (int i = 0; i < 6; i++) {
		cout << abilityScores[i] << endl;
	}
}

//! method to display the character
void Character::displayCharacter() {
	cout << "*******************************************" << endl;
	cout << "Here are you stats for your character " << endl;
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
	cout << "*******************************************";
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



void Character::setStrategy(Strategy* newStrategy) {
  this->strategy = newStrategy;
}

void Character::executeStrategy(Map& m) {
  this->strategy->execute(m, *this);
}

int Character::getCurrentPositionX() {
  return this->currentPosition[0];
}
int Character::getCurrentPositionY() {
  return this->currentPosition[1];
}
void Character::setCurrentPositionX(int charPosX) {
  this->currentPosition[0] = charPosX;
}
void Character::setCurrentPositionY(int charPosY) {
  this->currentPosition[1] = charPosY;
}
char Character::getTypeOnMap() {
  return this->typeOnMap;
}
void Character::setTypeOnMap(char t) {
  this->typeOnMap = t;
}


