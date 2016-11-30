#include "Fighter.h"

Fighter::Fighter() : Character() {};

Fighter::Fighter(CharacterAttr *characterAttr) : Character(characterAttr) {}

Fighter::~Fighter() {
	delete this;
}

void Fighter::setPlayerType(string playerType) {
	this->playerType = playerType;
}

string Fighter::getPlayerType() const {
	return this->playerType;
}

Bully::Bully(CharacterAttr *characterAttr) : Fighter(characterAttr){};

Bully::~Bully() {
	delete this;
}

Nimble::Nimble(CharacterAttr *characterAttr) : Fighter(characterAttr) {};

Nimble::~Nimble() {
	delete this;
}

Tank::Tank(CharacterAttr *characterAttr) : Fighter(characterAttr) {};

Tank::~Tank() {
	delete this;
}
