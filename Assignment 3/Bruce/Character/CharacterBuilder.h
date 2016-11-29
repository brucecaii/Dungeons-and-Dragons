#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H
#include "Fighter.h"
#include "../Dice/Dice.h"
#include "CharacterAttr.h"
using namespace std;

class CharacterBuilder {

public:
	CharacterBuilder(string fighterType, int level);
	Character* getCharacter();
	void createCharacter();
	virtual void setPlayerType() = 0;

protected:
	Fighter* c_character;
	string fighterType;
	int fighterLevel;
};

class PlayerCharacterBuilder : public CharacterBuilder {

public:
	PlayerCharacterBuilder(string fighterType, int level);
	void setPlayerType();

};

class EnermyCharacterBuilder : public CharacterBuilder {

public:
	EnermyCharacterBuilder(string fighterType, int level);
	void setPlayerType();

};

#endif