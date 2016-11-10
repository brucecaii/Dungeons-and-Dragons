#pragma once

#include "Subject.h"
#include <string>
#include "ItemContainer.h"
#include "json.hpp"
using json = nlohmann::json;


class Character : public Subject
{
public:
	Character();
	Character(int, int, int, int, int, int);
	~Character();
	void hit(int);
	int getHitPoints();
	void levelUp();
	int modifier(int);
	void showAbilityScores();
	void displayCharacter();
	
	//! getters for total scores
	int getStrength();
	int getDexterity();
	int getConstitution();
	int getIntelegence();
	int getWisdom();
	int getCharisma();
	int getLevel();

	//! getters for scores from your base attributes, not item enhancments
	int getStrengthFromBase();
	int getDexterityFromBase();
	int getConstitutionFromBase();
	int getIntelegenceFromBase();
	int getWisdomFromBase();
	int getCharismaFromBase();

	//! setters for your base character stats
	void setStrength(int);
	void setDexterity(int);
	void setConstitution(int);
	void setIntelegence(int);
	void setWisdom(int);
	void setCharisma(int);
	
	//!  following methods relate to the characters backpack and equipped items
	void addItemBackpack(Item);
	void removeItemfromBackpack(string);
	void equipItem(Item);
	void deEquipItem(string);
	void updatestats();
	void displayItemsEquipped();
	void displayItemsInBackPack();
        bool validateNewCharacter();

	ItemContainer* getBackpack();
	ItemContainer* getEquipment();



private:
	int lvl = 1;
	int abilityScores[6]; //! total ablityscore with items and  base scores aggregated
	int abilityScoresFromChar[6]; 
	int abilityScoresFromItems[6];
	int currentHitPoints;
	int modifers[6];
	int armorclass;
	int attackbonus;
	int damagebonus;
	int ArmorfromChar;
	int ArmorFromItems;
	int attackbonusFromChar;
	int attackbounusFromItems;
	ItemContainer *equipment;
	ItemContainer *backpack;



};

class Fighter : public Character {
public:
	Fighter();
	Fighter(int, int, int, int, int, int);
private:
};

