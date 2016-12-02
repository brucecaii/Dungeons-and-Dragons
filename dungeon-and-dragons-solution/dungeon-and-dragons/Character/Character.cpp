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

Character::Character() {
	this->characterLevel = 1;
	this->setHitPoint(10);
	this->setAttackBonus({1, 0, 0, 0});
	this->strategy = nullptr;
	this->armorClass = 10;
	this->setCharacterBackpack(new Backpack());
	this->setCharacterEquipment(new Backpack());
	this->damageBonus = 0;
}

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
}

Character::~Character() {
	delete this;
}

/*
action methods
*/

void Character::equipItem(Item item) {
	if (characterEquipment->getItemByType(item.getType()).getType()=="") {
		changeAttr(item.getEnhancement().getType(), item.getEnhancement().getBonus(), "+");
		characterEquipment->addItem(item);
	}
}

void Character::deEquipItem(string typeofItem) {
	if (characterEquipment->getItemByType(typeofItem).getType() == typeofItem) {
		Item current = characterEquipment->getItemByType(typeofItem);
		changeAttr(current.getEnhancement().getType(), current.getEnhancement().getBonus(), "-");
		characterEquipment->deleteItemByType(typeofItem);
	}
}

void Character::addItemBackpack(Item item) {
	if (characterBackpack->getItems().size() < 20) {
		characterBackpack->addItem(item);
	}
	else {
		cout << "your bag is full" << endl;
	}
}

void Character::removeItemfromBackpack(string name) {
	characterBackpack->deleteItem(name);
}

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

int Character::modifier(int dice, int bonus) const {
	return dice += bonus;
}

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
}

bool Character::validateNewCharacter() {
	return this->characterAttr->validateAttr();
}

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
			if (rand() % 100 + 1 < hitChance && damage > opponent->getArmorClass()) {
				isHit = true;
			}
			else isHit = false;
		}
		if (isHit) {
			opponent->setHitPoint(opponent->getHitPoint() - damage);
		}
	}
}

void Character::executeStrategy(Map& m) {
	this->strategy->execute(m, *this);
}

void Character::lootChest(ItemContainer* chest) {
	for (size_t i = 0; i < chest->getItems().size(); i++) {
		this->addItemBackpack(chest->getItems()[i]);
	}
}

void Character::lootCharacter(Character* character) {
	for (size_t i = 0; i < character->getCharacterBackpack()->getItems().size(); i++) {
		this->addItemBackpack(character->getCharacterBackpack()->getItems()[i]);
	}
	for (size_t i = 0; i < character->getCharacterEquipment()->getItems().size(); i++) {
		this->addItemBackpack(character->getCharacterEquipment()->getItems()[i]);
	}
}

/*
getter and setter
*/

void Character::setLevel(int level) {
	this->characterLevel = level;
}

int Character::getLevel() const {
	return this->characterLevel;
}

int Character::getHitPoint() const {
	return this->hitPoint;
}

void Character::setHitPoint(int hitPoint) {
	this->hitPoint = hitPoint;
}

int Character::getArmorClass() const {
	return this->armorClass;
}

void Character::setArmorClass(int armorClass) {
	this->armorClass = armorClass;
}

void Character::setDamageBonus(int damageBonus) {
	this->damageBonus += damageBonus;
}

int Character::getDamageBonus(){
	return this->damageBonus;
}

vector<int> Character::getAttackBonus() const {
	return this->attackbonus;
}

void Character::setAttackBonus(const vector<int> &attackBonus) {
	this->attackbonus = attackBonus;
}

ItemContainer* Character::getCharacterEquipment() const {
	return this->characterEquipment;
}

void Character::setCharacterEquipment(ItemContainer *characterEquipment) {
	this->characterEquipment = characterEquipment;
}

ItemContainer* Character::getCharacterBackpack() const {
	return this->characterBackpack;
}

void Character::setCharacterBackpack(ItemContainer *characterBackpack) {
	this->characterBackpack = characterBackpack;
}

CharacterAttr* Character::getCharacterAttr() const {
	return this->characterAttr;
}

void Character::setCharacterAttr(CharacterAttr *characterAttr) {
	this->characterAttr = characterAttr;
}

void Character::setStrategy(CharacterStrategy* newStrategy) {
  if (strategy != nullptr)
    delete this->strategy;
  this->strategy = newStrategy;
}

vector<int> Character::getCurrentPosition() {
  return this->currentPosition;
}

void Character::setCurrentPosition(vector<int> currentPosition) {
  this->currentPosition = currentPosition;
}

char Character::getTypeOnMap() {
  return this->typeOnMap;
}

void Character::setTypeOnMap(char t) {
  this->typeOnMap = t;
}
