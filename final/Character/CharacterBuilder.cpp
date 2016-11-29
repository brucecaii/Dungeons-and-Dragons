#include "CharacterBuilder.h"

CharacterBuilder::CharacterBuilder(string fighterType) {
	this->fighterType = fighterType;
}

Character* CharacterBuilder::getCharacter() {
	return this->c_character;
};

void CharacterBuilder::createCharacter() {
	vector<int> singleRoll;
	vector<int> ability;
	for (int i = 0; i < 6; i++) {
		singleRoll = Dice::roll("4d6");
		sort(singleRoll.begin(), singleRoll.end(), greater<int>());
		ability.push_back(singleRoll[0] + singleRoll[1] + singleRoll[2]);
	}
	sort(ability.begin(), ability.end(), greater<int>());
	if (this->fighterType == "Bully") {
		CharacterAttr *bullyAttr = new CharacterAttr(ability[3], ability[5], ability[0], ability[2], ability[1], ability[4]);
		this->c_character = new Bully(bullyAttr);
	}
	if (this->fighterType == "Nimble") {
		CharacterAttr *bullyAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[0], ability[1], ability[4]);
		this->c_character = new Nimble(bullyAttr);
	}
	if (this->fighterType == "Tank") {
		CharacterAttr *bullyAttr = new CharacterAttr(ability[3], ability[5], ability[2], ability[1], ability[0], ability[4]);
		this->c_character = new Tank(bullyAttr);
	}
};

PlayerCharacterBuilder::PlayerCharacterBuilder(string fighterType) : CharacterBuilder(fighterType) {};

void PlayerCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("player");
}

EnermyCharacterBuilder::EnermyCharacterBuilder(string fighterType) : CharacterBuilder(fighterType) {};

void EnermyCharacterBuilder::setPlayerType() {
	this->c_character->setPlayerType("enermy");
}