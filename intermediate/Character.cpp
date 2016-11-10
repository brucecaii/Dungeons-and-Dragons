
#include "Character.h"
#include <cmath>
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>      
#include <string>
using namespace std;


Fighter::Fighter() {}  //! default construtor for fighter
	

Character::Character() { //! default constutor for character
	this->equipment = new ItemContainer(); //! this stores equipped items
	this->backpack = new ItemContainer();  //! this is your backpack 
	
	//! if your default construtor is called you have no default values added yet
	abilityScores[0] = 0; abilityScoresFromChar[0] = 0; 
	abilityScores[1] = 0, abilityScoresFromChar[1] = 0;
	abilityScores[2] = 0, abilityScoresFromChar[2] = 0;
	abilityScores[3] = 0, abilityScoresFromChar[3] = 0;
	abilityScores[4] = 0, abilityScoresFromChar[4] = 0;
	abilityScores[5] = 0, abilityScoresFromChar[5] = 0;
}

//! Constructor: passes values to each ability score and set hit points to 10
Character::Character(int str, int dex, int con, int intel, int wis, int cha)
{

	this->equipment = new ItemContainer(); //! this stores equipped items
	this->backpack = new ItemContainer();  //! this is your backpack 

	//! your modifer values are stored here
	modifers[0] = modifier(str);  
	modifers[1] = modifier(dex);
	modifers[2] = modifier(con);
	modifers[3] = modifier(intel);
	modifers[4] = modifier(wis);
	modifers[5] = modifier(cha);

	//! intializing your total scores and base scores , will be same value on constuctor call
	abilityScores[0] = str; abilityScoresFromChar[0] = str;
	abilityScores[1] = dex, abilityScoresFromChar[1] = dex;
	abilityScores[2] = con, abilityScoresFromChar[2] = con;
	abilityScores[3] = intel, abilityScoresFromChar[3] = intel;
	abilityScores[4] = wis, abilityScoresFromChar[4] = wis;
	abilityScores[5] = cha, abilityScoresFromChar[5] = cha;

	//! set hit points to 10 and multyping it by consitution level, as consitution level influnces hitpoints and by lvl
	currentHitPoints = 10 + abilityScores[2];
	//!  base armor class is 10+ the modifer of your dexterity
	armorclass, ArmorfromChar = 10 + modifers[1];
	//! base attack bonus is your strength and dexterity modifers summed and multiplyed by level
	attackbonus, attackbonusFromChar = (modifers[0] + modifers[1])*lvl;
	damagebonus = modifers[0];
}

//! non default constructor for fighter class
Fighter::Fighter(int str, int dex, int con, int intel, int wis, int cha) : Character(str, dex, con, intel, wis, cha){

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

int Character::getIntelegence() {
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

int Character::getIntelegenceFromBase() {

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

void Character::setIntelegence(int i) { 
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
	updatestats();
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
void Character::hit(int damage)
{
	currentHitPoints = currentHitPoints - damage;
	//Notify();
}


//! @return int: value of currentHitPoints
int Character::getHitPoints()
{
	return currentHitPoints;
}


//! this displays the ability scores
void Character::showAbilityScores() {
	
	for (int i = 0; i < 6; i++) {
		cout << abilityScores[i] << endl;
	}
}


//! adds item to your backpack
void Character::addItemBackpack(Item i) {
	
	vector<Item> test = vector<Item>();
	test = backpack->getItems();

	if (test.size() < 20) {
		backpack->addItem(i);
	}
	else {
		cout << "your bag is full" << endl;
	}
}

//! Remove item from backpack by name
void Character::removeItemfromBackpack(string name) { 
	backpack->deleteItem(name);
}

//! equip an item to your character 
void Character::equipItem(Item i) {   
	vector<Item> test = vector<Item>();
	test = equipment->getItems();
	bool has = false;

	for (int z = 0; z < test.size(); z++) {
		if (test[z].getType() == i.getType()) {
			cout << "You arleady have an item of that type equipped, de-equip item type of interest first" << endl;
			has = true;
		}
	}

	if (!has) { // if type of the item is not already equipped you may equip
		equipment->addItem(i);
	}
	updatestats(); //update current stats with new item
}

//! de-equiping item of you, you pass the item type
void Character::deEquipItem(string typeofItem) {  

	equipment->deleteItemByType(typeofItem);

	updatestats(); //updatecurrent stats

}


//! this takes a look at all the items equipped, agggrates thes stats and add its to your base stats; 
void Character::updatestats() {
	vector<Item> test = vector<Item>(); 
	test = equipment->getItems(); // getting the items that you currently have equipped 
	currentHitPoints -= abilityScoresFromItems[2]; // choping off extra hp from items 
	for (int i = 0; i < 6; i++) {   // reseting bounuses from items
		abilityScoresFromItems[i] = 0;
	}

	for (int i = 0; i < test.size(); i++) {  // for each item you iterate over its enhancments to get total enchments given by an item
		vector<Enhancement> influence = vector<Enhancement>();

		influence = test[i].getInfluences(); // getting enchaments currently on item
		for (int z = 0; z < influence.size(); z++) {

			if (influence[z].getType() == "Strength") {

				abilityScoresFromItems[0] += influence[z].getBonus();
			}

			if (influence[z].getType() == "Dexterity") {

				abilityScoresFromItems[1] += influence[z].getBonus();
			}
			if (influence[z].getType() == "Constitution") {

				abilityScoresFromItems[2] += influence[z].getBonus();
			}
			if (influence[z].getType() == "Intelligence") {

				abilityScoresFromItems[3] += influence[z].getBonus();
			}
			if (influence[z].getType() == "Wisdom") {

				abilityScoresFromItems[4] += influence[z].getBonus();
			}

			if (influence[z].getType() == "Charisma") {

				abilityScoresFromItems[5] += influence[z].getBonus();
			}

			if (influence[z].getType() == "Armor class") {

				ArmorFromItems += influence[z].getBonus();
			}
			if (influence[z].getType() == "Attack bonus") {

				attackbounusFromItems += influence[z].getBonus();
			}
		}

	}

	for (int i = 0; i < 6; i++) {   // tallying up total bonuses from base states and enchaments 
		abilityScores[i] = abilityScoresFromChar[i] + abilityScoresFromItems[i];
	}
	armorclass = ArmorfromChar + ArmorFromItems + modifers[1]; // updating armor
	attackbonus = attackbonusFromChar + attackbounusFromItems + (modifers[0] + modifers[1])*lvl; // updating attackbonus
	currentHitPoints += abilityScoresFromItems[2]; // updating hp

	Notify();

}


ItemContainer* Character::getEquipment()  
{
	return this->equipment;
}

ItemContainer* Character::getBackpack()
{
	return this->backpack;
}