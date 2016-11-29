#include "CharacterAttr.h"

CharacterAttr::CharacterAttr() {
	setIntelligence(0);
	setWisdom(0);
	setStrength(0);
	setDexterity(0);
	setConstitution(0);
	setCharisma(0);
}

CharacterAttr::CharacterAttr(int intelligence, int wisdom, int strength, int dexterity, int constitution, int charisma) {
	setIntelligence(intelligence);
	setWisdom(wisdom);
	setStrength(strength);
	setDexterity(dexterity);
	setConstitution(constitution);
	setCharisma(charisma);
}

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

int CharacterAttr::getIntelligence() const {
	return intelligence;
}

void CharacterAttr::setIntelligence(int intelligence) {
	CharacterAttr::intelligence = intelligence;
}

int CharacterAttr::getWisdom() const {
	return wisdom;
}

void CharacterAttr::setWisdom(int wisdom) {
	CharacterAttr::wisdom = wisdom;
}

int CharacterAttr::getStrength() const {
	return strength;
}

void CharacterAttr::setStrength(int strength) {
	CharacterAttr::strength = strength;
}

int CharacterAttr::getDexterity() const {
	return dexterity;
}

void CharacterAttr::setDexterity(int dexterity) {
	CharacterAttr::dexterity = dexterity;
}

int CharacterAttr::getConstitution() const {
	return constitution;
}

void CharacterAttr::setConstitution(int constitution) {
	CharacterAttr::constitution = constitution;
}

int CharacterAttr::getCharisma() const {
	return charisma;
}

void CharacterAttr::setCharisma(int charisma) {
	CharacterAttr::charisma = charisma;
}

CharacterAttr::~CharacterAttr() {}

