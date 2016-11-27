 #pragma once

#include "Subject.h"
#include <string>
#include "ItemContainer.h"

//!  Hello welcome to my assgiment 1 Jason Tsalikis Id: 25892120
//! So to make a new character in dungeions and dragon you pass him in the 6 ability scores
//! Important to d and d is the modifer rules, which are your ability score -10 /2 ; if below 0 just add 0. Some games you can have a negative ablity score but we decided to go with the version that does not use negative modifers
//!
//!




class Character : public Subject
{
public:
	Character(); 
	Character(int, int, int, int, int, int);
	bool validateNewCharacter();
	void hit(int);
	int getHitPoints();
	void levelUp();
	int modifier(int);
	void showAbilityScores();
	int getStrength();
	int getDexterity();
	int getConstitution();
	int getIntelegence();
	int getWisdom();
	int getCharisma();
	void addItemBackpack(Item);
	void removeItemfromBackpack(string);
	void equipItem(Item);
	void deEquipItem(string);
	void updatestats();


private:
	int lvl = 1; 
	int abilityScores[6];
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
	
	 
		//std::string items[6]; //! ok this will be where items will be stored.
};

class Fighter : public Character {  
public:
	Fighter();
	Fighter(int, int, int, int, int, int);


private:
	

};

