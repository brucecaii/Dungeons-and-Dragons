#include "Character.h"
#include <cmath>
#include <iostream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>      
#include <string>
using namespace std;

Character::Character() {
	this->characterLevel = 1;
	this->setHitPoint(10);
	this->setAttackBonus({1, 0, 0, 0});
}

Character::Character(CharacterAttr *characterAttr) {
	this->characterAttr = characterAttr;
	this->characterLevel = 1;
	this->setHitPoint(10);
	this->setAttackBonus({ 1, 0, 0, 0 });
}

Character::~Character() {
	delete this;
}

/*
action methods
*/

void Character::equipItem(Item item) {
	if (characterEquipment->getItem(item.getType()).getType()=="") {
		for (int i = 0; i < item.getInfluences().size();  i++) {
			changeAttr(item.getInfluences()[i].getType(), item.getInfluences()[i].getBonus(), "+");
		}
		characterEquipment->addItem(item);
	}
}

void Character::deEquipItem(string typeofItem) {
	if (characterEquipment->getItem(typeofItem).getType() == typeofItem) {
		Item current = characterEquipment->getItem(typeofItem);
		for (int i = 0; i < current.getInfluences().size(); i++) {
			changeAttr(current.getInfluences()[i].getType(), current.getInfluences()[i].getBonus(), "-");
		}
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
}

int Character::modifier(int dice, int bonus) const {
	return dice += bonus;
}

void Character::levelUp() {
	if (this->getLevel() != 20) {
		this->characterLevel++;
		int conModifier = (this->getCharacterAttr()->getConstitution() - 10) / 2;
		vector<int> roll = Dice::roll("1d10");
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

/*
getter and setter
*/

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

