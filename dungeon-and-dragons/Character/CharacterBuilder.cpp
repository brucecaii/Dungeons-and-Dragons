#include "CharacterBuilder.h"
#include "HumanPlayerStrategy.h"
#include "FriendlyStrategy.h"
#include "AggressorStrategy.h"
#include "../GameData.h"


//! @method constructor, sets level and fighter type
//! @param string fighterType , represents type of fighter
//! @param int level, the level of the character
CharacterBuilder::CharacterBuilder(string fighterType, int level) {
	this->fighterType = fighterType;
	this->fighterLevel = level;
}

//! @method Character
//! @return reference to a character
Fighter* CharacterBuilder::getCharacter() {
	return this->c_character;
};


//! @method method creates a character, randomly creates valid ability scores and assigns them appropriately based off of type of fighter
//! @return void
void CharacterBuilder::createCharacter() {
	vector<int> singleRoll;
	vector<int> ability;
	for (int i = 0; i < 6; i++) {
		singleRoll = GameData::gameDice->roll("4d6");
		sort(singleRoll.begin(), singleRoll.end(), greater<int>());
		ability.push_back(singleRoll[0] + singleRoll[1] + singleRoll[2]);
	}
	sort(ability.begin(), ability.end(), greater<int>());
	if (this->fighterType == "Bully") {
		CharacterAttr *bullyAttr = new CharacterAttr(ability[3], ability[5], ability[0], ability[2], ability[1], ability[4]);
		this->c_character = new Bully(bullyAttr);
	}
	if (this->fighterType == "Nimble") {
		CharacterAttr *nimbleAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[0], ability[1], ability[4]);
		this->c_character = new Nimble(nimbleAttr);
	}
	if (this->fighterType == "Tank") {
		CharacterAttr *tankAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[1], ability[0], ability[4]);
		this->c_character = new Tank(tankAttr);
	}
	for (int i = 0; i < this->fighterLevel-1; i++) {
		this->c_character->levelUp();
	}
}

//! @method returns type of fighter
//! @return string denoting type of fighter
string CharacterBuilder::getFighterType()
{
	return this->fighterType;
}

//! @method returns level of your character
int CharacterBuilder::getFighterLevel()
{
	return this->fighterLevel;
}
;
//! method constructor for PlayerCharacterBuilder, calls parent constructor 
PlayerCharacterBuilder::PlayerCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};

//! @method sets type of player, strategy and map for a player character
//! @return void
void PlayerCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("player");
	this->c_character->setTypeOnMap('S');
        this->c_character->setStrategy(new HumanPlayerStrategy());
}

//! @method constructor for AggressorCharacterBuilder, calls its parents constructor
AggressorCharacterBuilder::AggressorCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};


//! @method sets player type, strategy, and map type for a character
void AggressorCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("aggressor");
	this->c_character->setTypeOnMap('O');
	this->c_character->setStrategy(new AggressorStrategy());
}
//! @method constructor for FriendlyCharacterBuilder, calls its parents constructor
FriendlyCharacterBuilder::FriendlyCharacterBuilder(string fighterType, int level) : CharacterBuilder(fighterType, level) {};

//! @method sets player type, strategy, and map type for a character
void FriendlyCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("friendly");
	this->c_character->setTypeOnMap('C');
	this->c_character->setStrategy(new FriendlyStrategy());
}

