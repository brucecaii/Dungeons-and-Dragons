#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H
#include "ItemContainer.h"
#include "Char.h"
//#include "CharacterAttr.h"

using namespace std;



class Character : public Char
{

public:
	Character();
	Character(CharacterAttr *characterAttr);
	~Character();
	/*
	action methods
	*/
	void equipItem(Item);
	void deEquipItem(string);
	void addItemBackpack(Item);
	void removeItemfromBackpack(string);
	void changeAttr(string type, int value, string action);
	int modifier(int dice, int bonus) const;
	void levelUp();
	bool validateNewCharacter();
	/*
	setter and getter
	*/
	int getLevel() const;
	int getHitPoint() const;
	void setHitPoint(int hitPoint);
	int getArmorClass() const;
	void setArmorClass(int armorClass);
	vector<int> getAttackBonus(); // dummy method
	vector<int> getAttackBonus() const;
	void setAttackBonus(const vector<int> &attackBonus);
	ItemContainer* getCharacterEquipment() const;
	void setCharacterEquipment(ItemContainer *characterEquipment);
	ItemContainer* getCharacterBackpack() const;
	void setCharacterBackpack(ItemContainer *characterBackpack);
	CharacterAttr* getCharacterAttr() const;
	void setCharacterAttr(CharacterAttr *characterAttr);

private:
	/*
	attributes
	*/
	int characterLevel;
	int armorClass;
	int hitPoint;
	vector<int> attackbonus;
	CharacterAttr *characterAttr;
	ItemContainer *characterEquipment;
	ItemContainer *characterBackpack;
};

#endif 

