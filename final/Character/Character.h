#ifndef CHARACTER_H
#define CHARACTER_H
#include "Subject.h"
#include "../item/ItemContainer.h"
#include "../Dependency/json.hpp"
#include "CharacterAttr.h"
#include "../Dice/Dice.h"
using json = nlohmann::json;
using namespace std;

class Character : public Subject {

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
	void attack(Character *opponent);
	/*
	setter and getter
	*/
	int getLevel() const;
	int getHitPoint() const;
	void setHitPoint(int hitPoint);
	int getArmorClass() const;
	void setArmorClass(int armorClass);
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

