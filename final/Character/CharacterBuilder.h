#ifndef CHARACTER_BUILDER_H
#define CHARACTER_BUILDER_H
#include "Fighter.h"
#include "../Dice/Dice.h"
#include "CharacterAttr.h"
using namespace std;

class CharacterBuilder {

public:
	CharacterBuilder(string fighterType);
	Character* getCharacter();
	void createCharacter();
	virtual void setPlayerType() = 0;

protected:
	Fighter* c_character;
	string fighterType;
};

class PlayerCharacterBuilder : public CharacterBuilder {

public:
	PlayerCharacterBuilder(string fighterType);
	void setPlayerType();

};

class EnermyCharacterBuilder : public CharacterBuilder {

public:
	EnermyCharacterBuilder(string fighterType);
	void setPlayerType();

};

#endif