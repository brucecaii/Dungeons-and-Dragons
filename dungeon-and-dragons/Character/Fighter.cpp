#include "Fighter.h"
//! @method default constructor
Fighter::Fighter() : Character() {};

//! @method constructor for figther, takes in Character Attributes
//! @param reference to CharacterAttr 
Fighter::Fighter(CharacterAttr *characterAttr) : Character(characterAttr) {}

//! @method destructor
Fighter::~Fighter() {
	delete this;
}

//! @method sets type of fighter
//! @param string player, denotes the type of fighter
void Fighter::setPlayerType(string playerType) {
	this->playerType = playerType;
}

//! @method returns the type of fighter
//! @return string representing the type of player
string Fighter::getPlayerType() const {
	return this->playerType;
}

//! @method constructor for a bully fighter
//! @param reference to a CharacterAttr
Bully::Bully(CharacterAttr *characterAttr) : Fighter(characterAttr){};

Bully::~Bully() {
	delete this;
}
//! @method constructor for a nimble fighter
//! @param reference to a CharacterAttr
Nimble::Nimble(CharacterAttr *characterAttr) : Fighter(characterAttr) {};


Nimble::~Nimble() {
	delete this;
}

//! @method constructor for a tank fighter
//! @param reference to a CharacterAttr
Tank::Tank(CharacterAttr *characterAttr) : Fighter(characterAttr) {};

Tank::~Tank() {
	delete this;
}
