#pragma once

#ifndef CHAR_H
#define CHAR_H
#include <string>
#include <vector>
#include "CharacterAttr.h"

using namespace std;


class Item;
class ItemContainer;
class CharacterAttr;
class Char {

public:
	
	Char();
	~Char();
	// action methods
virtual		void equipItem(Item);
virtual		void deEquipItem(string);
virtual		void addItemBackpack(Item);
virtual		void removeItemfromBackpack(string);
virtual void changeAttr(string type, int value, string action);
virtual int modifier(int dice, int bonus) const;
virtual void levelUp();
virtual bool validateNewCharacter();



// setter getters
virtual int getLevel() const;
virtual int getHitPoint() const;
virtual void setHitPoint(int hitPoint);
virtual int getArmorClass() const;
virtual void setArmorClass(int armorClass);
virtual vector<int> getAttackBonus(); 
virtual void setAttackBonus(const vector<int> &attackBonus);


virtual ItemContainer* getCharacterEquipment() const;

virtual void setCharacterEquipment(ItemContainer *characterEquipment);
virtual ItemContainer* getCharacterBackpack() const;
virtual void setCharacterBackpack(ItemContainer *characterBackpack);
virtual CharacterAttr* getCharacterAttr() const;
virtual void setCharacterAttr(CharacterAttr *characterAttr);



};
#endif 