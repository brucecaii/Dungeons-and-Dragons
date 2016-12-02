#include "Character.h"
#include "CharacterStrategy.h"
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "../GameData.h"
using namespace std;

//! @method Default Constructor for character
//! @return void
Character::Character() {
	this->characterLevel = 1;
	this->setHitPoint(10);
	this->setAttackBonus({1, 0, 0, 0});
	this->strategy = nullptr;
	this->armorClass = 10;
	this->setCharacterBackpack(new Backpack());
	this->setCharacterEquipment(new Backpack());
	this->damageBonus = 0;
	this->typeOnMap = 'C';
}

//! @method Constructor Character, takes in reference to CharacterAttr, which is the values for the ability scores
//! @return void
Character::Character(CharacterAttr *characterAttr) {
	this->characterAttr = characterAttr;
	this->characterLevel = 1;
	this->setHitPoint(10);
	this->setAttackBonus({ 1, 0, 0, 0 });
	this->strategy = nullptr;
	this->armorClass = 10;
	this->setCharacterBackpack(new Backpack());
	this->setCharacterEquipment(new Backpack());
	this->damageBonus = 0;
	this->typeOnMap = 'C';
}


//! @method destructor 
Character::~Character() {
	delete this;
}

/*
action methods
*/


//! @method adds item to characters equipment container, removes that item from characters backpack, observers are notified of change of state 
//! @param instance of item
//! @return void
void Character::equipItem(Item item) {
	if (this->characterEquipment->getItemByType(item.getType()).getType()=="") {
		this->changeAttr(item.getEnhancement().getType(), item.getEnhancement().getBonus(), "+");
		this->characterEquipment->addItem(item);
		this->characterBackpack->deleteItem(item.getName());
	}
	else if (this->characterEquipment->getItemByType(item.getType()).getType() == item.getType()) {
		this->changeAttr(
			this->characterEquipment->getItemByType(item.getType()).getEnhancement().getType(),
			this->characterEquipment->getItemByType(item.getType()).getEnhancement().getBonus(),
			"-"
		);
		this->characterBackpack->addItem(this->characterEquipment->getItemByType(item.getType()));
		this->characterEquipment->deleteItemByType(item.getType());
		this->changeAttr(item.getEnhancement().getType(), item.getEnhancement().getBonus(), "+");
		this->characterEquipment->addItem(item);
		this->characterBackpack->deleteItem(item.getName());
	}

	Notify();
}


//! @method removes an item from your equipment container
//! @param string denoting the type of item
//! @return void
void Character::deEquipItem(string typeofItem) {
	if (characterEquipment->getItemByType(typeofItem).getType() == typeofItem) {
		Item current = characterEquipment->getItemByType(typeofItem);
		changeAttr(current.getEnhancement().getType(), current.getEnhancement().getBonus(), "-");
		characterEquipment->deleteItemByType(typeofItem);
		Notify();
	}
}

//! @method adds item to your backpack container 
//! @param instance of Item
//! @return void
void Character::addItemBackpack(Item item) {
	if (characterBackpack->getItems().size() < 20) {
		characterBackpack->addItem(item);
	}
	else {
		cout << "your bag is full" << endl;
	}
}

//! @method removes item from backpack container
//! @param string denoted the name of an item 
//! @return void
void Character::removeItemfromBackpack(string name) {
	characterBackpack->deleteItem(name);
}

//! @method modifies the attributes associated to a character
//! @param string type denoting the type of attribute to be modified
//! @param int value denoting the value to be added or deducted to an attribute
//! @param string action denotes whether value will be added or deducted from attribute
//! @return void
void Character::changeAttr(string type, int value, string action) {
	if (type.compare("int") == 0) {
		if (action == "+") this->characterAttr->setIntelligence(this->characterAttr->getIntelligence() + value);
		if (action == "-") this->characterAttr->setIntelligence(this->characterAttr->getIntelligence() - value);
	}
	else if (type.compare("wis") == 0) {
		if (action == "+") this->characterAttr->setWisdom(this->characterAttr->getWisdom() + value);
		if (action == "-") this->characterAttr->setWisdom(this->characterAttr->getWisdom() - value);
	}
	else if (type.compare("str") == 0) {
		if (action == "+") this->characterAttr->setStrength(this->characterAttr->getStrength() + value);
		if (action == "-") this->characterAttr->setStrength(this->characterAttr->getStrength() - value);
	}
	else if (type.compare("con") == 0) {
		if (action == "+") this->characterAttr->setConstitution(this->characterAttr->getConstitution() + value);
		if (action == "-") this->characterAttr->setConstitution(this->characterAttr->getConstitution() - value);
	}
	else if (type.compare("cha") == 0) {
		if (action == "+") this->characterAttr->setCharisma(this->characterAttr->getCharisma() + value);
		if (action == "-") this->characterAttr->setCharisma(this->characterAttr->getCharisma() - value);
	}
	else if (type.compare("dex") == 0) {
		if (action == "+") this->characterAttr->setDexterity(this->characterAttr->getDexterity() + value);
		if (action == "-") this->characterAttr->setDexterity(this->characterAttr->getDexterity() - value);
	}
	else if (type.compare("arm") == 0) {
		if (action == "+") this->setArmorClass(this->getArmorClass() + value);
		if (action == "-") this->setArmorClass(this->getArmorClass() - value);
	}
	else if (type.compare("dmg") == 0) {
		if (action == "+") this->setDamageBonus(this->getDamageBonus() + value);
		if (action == "-") this->setDamageBonus(this->getDamageBonus() - value);
	}
}


//! @method modifies a bonus based on a dice value
//! @param int dice 
//! @param int bonus
//! @return the bonus added to the dice value 
int Character::modifier(int dice, int bonus) const {
	return dice += bonus;
}

//! @method levels the character up one level from its current, checks range of accepted of levels and updates values that scale
//! @return void
void Character::levelUp() {
	if (this->getLevel() != 20) {
		this->characterLevel++;
		int conModifier = (this->getCharacterAttr()->getConstitution() - 10) / 2;
		if (conModifier <= 0) conModifier = 0;
		vector<int> roll = GameData::gameDice->roll("1d10");
		int hitPointIncrease = modifier(roll[0], conModifier);
		if (hitPointIncrease < 1) hitPointIncrease = 1;
		this->setHitPoint(this->getHitPoint() + hitPointIncrease);
		vector<int> attackBonus;
		attackBonus.push_back(this->getLevel());
		if (this->getLevel() - 5 > 0) {
			attackBonus.push_back(this->getLevel() - 5);
		}
		else {
			attackBonus.push_back(0);
		}
		if (this->getLevel() - 10 > 0) {
			attackBonus.push_back(this->getLevel() - 10);
		}
		else {
			attackBonus.push_back(0);
		}
		if (this->getLevel() - 15 > 0) {
			attackBonus.push_back(this->getLevel() - 15);
		}
		else {
			attackBonus.push_back(0);
		}
		this->setAttackBonus(attackBonus);
	}
	Notify();
}

//! @method validates whether character attributes are within legal range 
//! @return boolean representing whether character was valid or not 
bool Character::validateNewCharacter() {
	return this->characterAttr->validateAttr();
}

//! @method records a hit onto an opposing character, takes into account armor class, attack bonuses , damage bonuses, and dice rolls
//! @param a reference to the character you will hit 
//! @return void
void Character::attack(Character *opponent) {
	for (int i = 0; i < 4; i++) {
		if (this->getAttackBonus()[i] == 0) break;
		int damage;
		bool isHit;
		int attackRoll = GameData::gameDice->roll("1d20")[0];
		damage = this->getAttackBonus()[i] + this->getDamageBonus();
		if (attackRoll == 20) isHit = true;
		else if (attackRoll == 1) isHit = false;
		else {
			double hitChance = (double(attackRoll) / double(20)) * 100;
			if (rand() % 100 + 1 < hitChance && this->getAttackBonus()[i] + attackRoll > opponent->getArmorClass()) {
				isHit = true;
			}
			else isHit = false;
		}
		if (isHit) {
			opponent->setHitPoint(opponent->getHitPoint() - damage);
		}
	}
}

//! @method executes a strategy pattern for character
//! @param reference to a map 
//! @return void
void Character::executeStrategy(Map& m) {
	this->strategy->execute(m, *this);
}

//! @method Character takes the items in a chest and adds them to his backpack container
//! @param reference to an item container which will be the chest character is looting
//! @return void
void Character::lootChest(ItemContainer* chest) {
	for (size_t i = 0; i < chest->getItems().size(); i++) {
		this->addItemBackpack(chest->getItems()[i]);
	}
}

//! @method Character loots another character
//! @param reference to a character you will loot
//! @return void
void Character::lootCharacter(Character* character) {
	for (size_t i = 0; i < character->getCharacterBackpack()->getItems().size(); i++) {
		this->addItemBackpack(character->getCharacterBackpack()->getItems()[i]);
	}
	for (size_t i = 0; i < character->getCharacterEquipment()->getItems().size(); i++) {
		this->addItemBackpack(character->getCharacterEquipment()->getItems()[i]);
	}
}

//! @method determines type of character you are
//! @param a char(single letter)
//! @return string denoting type of character you are
string Character::getTypeInString()
{
	string objName;
	char c = this->getTypeOnMap();
	if (c == 'S')
		objName = "Human Character";
	if (c == 'C')
		objName = "Friendly Character";
	if (c == 'O')
		objName = "Aggressor Character";
	return objName;
}

//! @method displays relevant attributes of a character 
//! @return void
void Character::displayCharacterInfo()
{
	//Getting attributes of character
	auto characterAttributes = this->getCharacterAttr();
	auto attackBonus = this->getAttackBonus();

	string currentCharType = getTypeInString();
	string currentLevel = to_string(this->getLevel());
	string currentHitPoint = to_string(this->getHitPoint());
	string currentArmorClass= to_string(this->getArmorClass());
	string currentDex = to_string(characterAttributes->getDexterity());
	string currentConst = to_string(characterAttributes->getConstitution());
	string currentCharisma = to_string(characterAttributes->getCharisma());
	string currentInt = to_string(characterAttributes->getIntelligence());
	string currentStr = to_string(characterAttributes->getStrength());
	string currentWisdom = to_string(characterAttributes->getWisdom());
	string currentDamageBonus = to_string(this->getDamageBonus());
	string currentAttackBonus = "[";

	for (size_t i = 0; i < attackBonus.size(); i++)
	{
		if (i == attackBonus.size() - 1)
		{
			currentAttackBonus += to_string(attackBonus[i]) + "]";
		} else {
			currentAttackBonus += to_string(attackBonus[i]) + ", ";
		}
	}

	cout << "=======================================================" << endl;
	cout << currentCharType + " - " + "Level " + currentLevel << endl;
	cout << "=======================================================" << endl;
	cout << "HP: " + currentHitPoint << endl;
	cout << "Armor Class: " + currentArmorClass << endl;
	cout << "Dexterity: " + currentDex << endl;
	cout << "Constitution: " + currentConst << endl;
	cout << "Strength: " + currentStr << endl;
	cout << "Intelligence: " + currentInt << endl;
	cout << "Charisma: " + currentCharisma << endl;
	cout << "Wisdom: " + currentWisdom << endl;
	cout << "Damage Bonus: " + currentDamageBonus << endl;
	cout << "Attack Bonus: " + currentAttackBonus << endl;
}

//! @method displays the name, type of item, type of enchantments, and bonuses of all items in characters equipment container 
//! @return void
void Character::displayCharacterEquipment() {
	cout << "======================" << endl <<
		"Character Gears" << endl <<
		"======================" << endl;
	for (size_t i = 0; i < this->getCharacterEquipment()->getItems().size(); i++) {
		Item currentItem = this->getCharacterEquipment()->getItems()[i];
		cout << "[" << currentItem.getType() << "] "
			<< "Name: " << currentItem.getName() << " || "
			<< currentItem.getEnhancement().getType() << " +"
			<< currentItem.getEnhancement().getBonus() << endl;
	}
}

//! @method displays the name, type of item, type of enchantments, and bonuses of all items in characters backpack container 
//! @return void
void Character::displayCharacterBackpack() {
	cout << "======================" << endl <<
		"Character Inventory" << endl <<
		"======================" << endl;
	for (size_t i = 0; i < this->getCharacterBackpack()->getItems().size(); i++) {
		Item currentItem = this->getCharacterBackpack()->getItems()[i];
		cout << "[" << i+1 << "] "
			<< "Type: " << currentItem.getType() << " || "
			<< "Name: " << currentItem.getName() << " || "
			<< currentItem.getEnhancement().getType() << " +"
			<< currentItem.getEnhancement().getBonus() << endl;
	}
}

/*
getter and setter
*/

//! @method sets the level of the character
void Character::setLevel(int level) {
	this->characterLevel = level;
}

//! @method gets the current level of the character
//! @return int representing the level of the character
int Character::getLevel() const {
	return this->characterLevel;
}

//! @method gets your current hitpoints(health)
//! @return int representing your current hitpoints
int Character::getHitPoint() const {
	return this->hitPoint;
}

//! @method sets your current hitpoints to an integer value
//! @param int hitpoint denoting the hp you will set your character to 
void Character::setHitPoint(int hitPoint) {
	this->hitPoint = hitPoint;
	Notify();
}

//! @method returns your amour class value
//! @return int of your armor class value
int Character::getArmorClass() const {
	return this->armorClass;
}

//! @method sets your armor class to a certain value
//! @param int armorClass, the value to which you will set your armorclass to
void Character::setArmorClass(int armorClass) {
	this->armorClass = armorClass;
}

//! @method sets your damage bonus to a certain value
//! @param int damageBonus 
void Character::setDamageBonus(int damageBonus) {
	this->damageBonus += damageBonus;
}

//! @method gets your damage bonus
//! @return int representing your damage bonus
int Character::getDamageBonus(){
	return this->damageBonus;
}

//! @method returns your attackbonus
//! @return vector of type int containing your attack bonuses
vector<int> Character::getAttackBonus() const {
	return this->attackbonus;
}

//! @method sets attack bonus
//! @param reference to a vector of type int representing the attack bonuses
void Character::setAttackBonus(const vector<int> &attackBonus) {
	this->attackbonus = attackBonus;
}

//! @method returns the item container that holds your equiped items 
//! @return refernce to ItemContainer
ItemContainer* Character::getCharacterEquipment() const {
	return this->characterEquipment;
}

//! @method sets characters Equipment container
//! @param  reference to an item container 
void Character::setCharacterEquipment(ItemContainer *characterEquipment) {
	this->characterEquipment = characterEquipment;
}

//! @method returns the item container that holds your backpack items 
//! @return refernce to ItemContainer
ItemContainer* Character::getCharacterBackpack() const {
	return this->characterBackpack;
}

//! @method sets characters Backpack container
//! @param  reference to an item container
void Character::setCharacterBackpack(ItemContainer *characterBackpack) {
	this->characterBackpack = characterBackpack;
}

//! @method gets your character attributes
//! @return reference to your character attributes 
CharacterAttr* Character::getCharacterAttr() const {
	return this->characterAttr;
}

//! @method sets characters attributes
//! @param refence to instance of attributes
void Character::setCharacterAttr(CharacterAttr *characterAttr) {
	this->characterAttr = characterAttr;
}

//! @method sets a stratgety for a character
//! @param reference to a strategy
void Character::setStrategy(CharacterStrategy* newStrategy) {
  if (strategy != nullptr)
    delete this->strategy;
  this->strategy = newStrategy;
}

//! @method gets characters position
//! @return vector of type int denoting characters position
vector<int> Character::getCurrentPosition() {
  return this->currentPosition;
}

//! @method sets position of a character
//! @param vector of ints representing coordinates of charactes position
void Character::setCurrentPosition(vector<int> currentPosition) {
  this->currentPosition = currentPosition;
}


//! @method returns type of map character is on
//! @return char denoting type of map
char Character::getTypeOnMap() {
  return this->typeOnMap;
}

//! @method sets map type
//! @param char representing type of map
void Character::setTypeOnMap(char t) {
  this->typeOnMap = t;
}


