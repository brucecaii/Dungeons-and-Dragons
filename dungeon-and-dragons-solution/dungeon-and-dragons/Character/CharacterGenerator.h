#ifndef CHARACTER_GENERATOR_H
#define CHARACTER_GENERATOR_H
#include "CharacterBuilder.h"
#include "../Subject.h"

class CharacterGenerator : public Subject {

public:
	void setCharacterBuilder(CharacterBuilder* cb);
	Character* getCharacter();
	void createCharacter();

private:
	CharacterBuilder* c_characterBuilder;

};

#endif
