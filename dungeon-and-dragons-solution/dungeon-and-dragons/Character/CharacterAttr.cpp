#include "CharacterAttr.h"


//! @method Default constructor 
CharacterAttr::CharacterAttr() {
	setIntelligence(0);
	setWisdom(0);
	setStrength(0);
	setDexterity(0);
	setConstitution(0);
	setCharisma(0);
}

//! @method takes in paramters and sets them for CharacterAttr
CharacterAttr::CharacterAttr(int intelligence, int wisdom, int strength, int dexterity, int constitution, int charisma) {
	setIntelligence(intelligence);
	setWisdom(wisdom);
	setStrength(strength);
	setDexterity(dexterity);
	setConstitution(constitution);
	setCharisma(charisma);
}

//! @ method validates the attributes 
//! @return boolean denoted whether attributes are valid or not
bool CharacterAttr::validateAttr() {
	const int MIN = 3;
	const int MAX = 18;
	return !(
		(getCharisma() < MIN || getCharisma() > MAX) ||
		(getConstitution() < MIN || getConstitution() > MAX) ||
		(getDexterity() < MIN || getDexterity() > MAX) ||
		(getIntelligence() < MIN || getIntelligence() > MAX) ||
		(getWisdom() < MIN || getWisdom() > MAX) ||
		(getStrength() < MIN || getStrength() > MAX)
		);
}

//! @method return intellegence
int CharacterAttr::getIntelligence() const {
	return intelligence;
}
//! @method sets intellgence
void CharacterAttr::setIntelligence(int intelligence) {
	CharacterAttr::intelligence = intelligence;
}
//! @method return wisdom
int CharacterAttr::getWisdom() const {
	return wisdom;
}
//! @method sets wisdom
void CharacterAttr::setWisdom(int wisdom) {
	CharacterAttr::wisdom = wisdom;
}
//! @method return strength
int CharacterAttr::getStrength() const {
	return strength;
}
//! @method sets strength
void CharacterAttr::setStrength(int strength) {
	CharacterAttr::strength = strength;
}
//! @method return dexterity
int CharacterAttr::getDexterity() const {
	return dexterity;
}
//! @method sets dexterity
void CharacterAttr::setDexterity(int dexterity) {
	CharacterAttr::dexterity = dexterity;
}
//! @method return constitution
int CharacterAttr::getConstitution() const {
	return constitution;
}
//! @method sets constitution
void CharacterAttr::setConstitution(int constitution) {
	CharacterAttr::constitution = constitution;
}
//! @method return Charisma
int CharacterAttr::getCharisma() const {
	return charisma;
}
//! @method sets Charisma
void CharacterAttr::setCharisma(int charisma) {
	CharacterAttr::charisma = charisma;
}
//! @method destructor
CharacterAttr::~CharacterAttr() {}

