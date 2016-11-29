#pragma once

#include <string>
#include "Map.h"

class Strategy;

//! A class representing a character, whether friendly or unfriendly.
class Character {
public:
	Character(int str, int dex, int con, int intel, int wis, int cha, Strategy* initStrategy, int posX, int posY, char typeOnMap);
	int getHitPoints();
	void setHitPoints(int HP);
	void levelUp();
	int modifier(int);
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

//! Implement character (friendly or unfriendly) actions as strategy pattern
//! Each turn, a character can proceed with:
//! - move
//! - attack
//! - free action
//!
//! Must implement these ConcreteStrategies:
//! 1) a HumanPlayerStrategy that lets the user decide where to move, who to attack, and what free actions to take;
//! 2) an AggressorStrategy that make the character automatically move towards and attack the player character;
//! 3) a FriendlyStrategy that makes the character automatically move towards the character, but not attack unless attacked, in which case it adopts the AggressorStrategy.klA
//!
//! Strategy is the abstract class that all above ConcreteClasses extend from.
class Strategy {
  public:
    virtual void execute(Map& m, Character& character) = 0;
    virtual void moveUp(Map& m, Character& character) = 0;
    virtual void moveDown(Map& m, Character& character) = 0;
    virtual void moveRight(Map& m, Character& character) = 0;
    virtual void moveLeft(Map& m, Character& character) = 0;
};


