//! @file 
//! @brief Header file for the Character class  
//!

#pragma once

//! Class that implements a character 
class Character
{
public:
	Character();
	Character(int, int, int, int, int, int);
	bool validateNewCharacter();
	void hit(int);
	int getHitPoints();
private: 
	int abilityScores[6];
	int currentHitPoints;
};

