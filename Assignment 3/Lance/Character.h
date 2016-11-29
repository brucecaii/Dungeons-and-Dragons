#pragma once

#include <string>
#include "Map.h"

class Strategy;

class Character {
public:
	Character(int str, int dex, int con, int intel, int wis, int cha, Strategy* initStrategy, int posX, int posY, char typeOnMap);
	void hit(int);
	int getHitPoints();
	void levelUp();
	int modifier(int);
	void showAbilityScores();
	void displayCharacter();
        bool validateNewCharacter();

	//! getters for total scores
	int getStrength();
	int getDexterity();
	int getConstitution();
	int getIntelligence();
	int getWisdom();
	int getCharisma();
	int getLevel();

	//! getters for scores from your base attributes, not item enhancments
	int getStrengthFromBase();
	int getDexterityFromBase();
	int getConstitutionFromBase();
	int getIntelligenceFromBase();
	int getWisdomFromBase();
	int getCharismaFromBase();

	//! setters for your base character stats
	void setStrength(int);
	void setDexterity(int);
	void setConstitution(int);
	void setIntelligence(int);
	void setWisdom(int);
	void setCharisma(int);

        void setTypeOnMap(char t);
        char getTypeOnMap();

        // relates to a character moving on a map.
        bool setCurrentPosition(Map m);
        int getCurrentPositionX();
        int getCurrentPositionY();
        void setCurrentPositionX(int charPosX);
        void setCurrentPositionY(int charPosY);
        void setStrategy(Strategy* newStrategy);
        void executeStrategy(Map& m);

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
        vector<int> currentPosition;
        Strategy *strategy;
        char typeOnMap;
};

class Strategy {
  public:
    virtual void execute(Map& m, Character& character) = 0;
};


