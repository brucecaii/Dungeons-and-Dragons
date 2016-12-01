#ifndef CHARACTER_H
#define CHARACTER_H
#include "../Item/ItemContainer.h"
#include "../Dependency/json.hpp"
#include "CharacterAttr.h"
#include "CharacterStrategy.h"
#include "../Map/Map.h"
#include "../Dice/Dice.h"
using json = nlohmann::json;
using namespace std;

class CharacterStrategy; // This forward declaration is needed. _DONT_TOUCH_IT_! (Lance)

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
	void executeStrategy(Map& m);
	void lootChest(ItemContainer* chest);
	void lootCharacter(Character* character);
	string getTypeInString(char c);
	void display();
	/*
	setter and getter
	*/
	void setLevel(int level);
	int getLevel() const;
	int getHitPoint() const;
	void setHitPoint(int hitPoint);
	int getArmorClass() const;
	void setArmorClass(int armorClass);
	vector<int> getAttackBonus() const;
	void setDamageBonus(int dmg);
	int getDamageBonus();
	void setAttackBonus(const vector<int> &attackBonus);
	ItemContainer* getCharacterEquipment() const;
	void setCharacterEquipment(ItemContainer *characterEquipment);
	ItemContainer* getCharacterBackpack() const;
	void setCharacterBackpack(ItemContainer *characterBackpack);
	CharacterAttr* getCharacterAttr() const;
	void setCharacterAttr(CharacterAttr *characterAttr);
	char getTypeOnMap();
	void setTypeOnMap(char type);
	vector<int> getCurrentPosition();
	void setCurrentPosition(vector<int> currentPosition);
	void setStrategy(CharacterStrategy* newStrategy);
	CharacterAttr *characterAttr;

private:
	/*
	attributes
	*/
	int characterLevel;
	int armorClass;
	int hitPoint;
	int damageBonus;
	char typeOnMap;
	vector<int> attackbonus;
	vector<int> currentPosition;
	ItemContainer *characterEquipment;
	ItemContainer *characterBackpack;
	CharacterStrategy *strategy;
};

#endif
