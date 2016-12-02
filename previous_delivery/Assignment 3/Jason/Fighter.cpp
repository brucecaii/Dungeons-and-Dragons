#include "Fighter.h"

Fighter::Fighter() : Character() {};

Fighter::Fighter(CharacterAttr *characterAttr) : Character(characterAttr) {}

Fighter::~Fighter() {
	delete this;
}