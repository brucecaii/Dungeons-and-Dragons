#include "CharacterGenerator.h"

void CharacterGenerator::setCharacterBuilder(CharacterBuilder* cb) {
	this->c_characterBuilder = cb;
};

Character* CharacterGenerator::getCharacter() {
	return this->c_characterBuilder->getCharacter();
}

void CharacterGenerator::createCharacter() {
	c_characterBuilder->createCharacter();
    c_characterBuilder->setPlayerType();
	UpdateLog("CharacterGenerator", "createCharacter", "Fighter created of type " + c_characterBuilder->getFighterType() + " and level " + to_string(c_characterBuilder->getFighterLevel()));
};
