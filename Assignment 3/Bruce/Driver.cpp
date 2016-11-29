//! @file 
//! @brief Driver file to create and execute the test suite 
//!
#include <string>
#include "Character/CharacterGenerator.h"
#include <iostream>
using namespace std;

int main() {

	CharacterGenerator selectHero;
	//prompt player config
	cout << endl << "Enter type of fighter (Bully, Tank, or Nimble) you wish you use: " << endl;
	string fighterType1;
	cin >> fighterType1;
	CharacterBuilder* playerBuilder = new PlayerCharacterBuilder(fighterType1);
	//prompt enermy config
	cout << endl << "Enter type of fighter (Bully, Tank, or Nimble) you wish your enermy to be: " << endl;
	string fighterType2;
	cin >> fighterType2;
	CharacterBuilder* enermyBuilder = new EnermyCharacterBuilder(fighterType2);
	//config generator
	selectHero.setCharacterBuilder(playerBuilder);
	selectHero.createCharacter();
	Character *player = selectHero.getCharacter();
	selectHero.setCharacterBuilder(enermyBuilder);
	selectHero.createCharacter();
	Character *enermy = selectHero.getCharacter();
	//let's print!
	srand(time(0));
	cout << "Ok, here is what you have:" << endl;
	cout << "Your character is a " << fighterType1 << endl;
	cout << "with following stats: " << endl;
	cout << "int " << player->getCharacterAttr()->getIntelligence() << " - "
		<< "wis " << player->getCharacterAttr()->getWisdom() << " - "
		<< "str " << player->getCharacterAttr()->getStrength() << " - "
		<< "con " << player->getCharacterAttr()->getConstitution() << " - "
		<< "dex " << player->getCharacterAttr()->getDexterity() << " - "
		<< "cha " << player->getCharacterAttr()->getCharisma() << " - "
		<< endl << "Hit Point at +" << player->getHitPoint() << endl;
	cout << "Bonus attack at: " << endl;
	for (int j = 0; j < 4; j++) {
		cout << "round " << j << ": attack bonus + " << player->getAttackBonus()[j] << endl;
	}
	for (int i = 0; i < 11; i++) player->levelUp();
	cout << "Now let's level up to level 11. After level up you have " << player->getHitPoint() << " hit points." << endl;
	cout << "Bonus attack at: " << endl;
	for (int k = 0; k < 4; k++) {
		cout << "round " << k << ": attack bonus + " << player->getAttackBonus()[k] << endl;
	}
	cout << "Your enermy character is a " << fighterType2 << endl;
	cout << "with following stats: " << endl;
	cout << "int " << enermy->getCharacterAttr()->getIntelligence() << " - "
		<< "wis " << enermy->getCharacterAttr()->getWisdom() << " - "
		<< "str " << enermy->getCharacterAttr()->getStrength() << " - "
		<< "con " << enermy->getCharacterAttr()->getConstitution() << " - "
		<< "dex " << enermy->getCharacterAttr()->getDexterity() << " - "
		<< "cha " << enermy->getCharacterAttr()->getCharisma() << " - "
		<< endl << "Hit Point at +" << enermy->getHitPoint() << endl;
	cout << "Bonus attack at: " << endl;
	for (int j = 0; j < 4; j++) {
		cout << "round " << j << ": attack bonus + " << enermy->getAttackBonus()[j] << endl;
	}
	for (int i = 0; i < 11; i++) enermy->levelUp();
	cout << "Now let's level up to level 11. After level up you have " << enermy->getHitPoint() << " hit points." << endl;
	cout << "Bonus attack at: " << endl;
	for (int k = 0; k < 4; k++) {
		cout << "round " << k << ": attack bonus + " << enermy->getAttackBonus()[k] << endl;
	}
	//prompt close console
	int i = 1;
	while (i == 1) {
		cout << endl << "Enter 0 to quit the program." << endl;
		cin >> i;
	}
	return 0;
}

