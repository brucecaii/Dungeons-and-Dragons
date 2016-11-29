#ifndef CHARACTER_GENERATOR_H
#define CHARACTER_GENERATOR_H
#include "CharacterBuilder.h"

class CharacterGenerator {

public:
	void setCharacterBuilder(CharacterBuilder* cb);
	Character* getCharacter();
	void createCharacter();

private:
	CharacterBuilder* c_characterBuilder;

};

#endif