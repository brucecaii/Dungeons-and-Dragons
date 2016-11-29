//! @file 
//! @brief Driver file to create and execute the test suite 
//!
#include <string>
#include "Item.h"
#include "Fighter.h"
#include "Enhancement.h"
#include "CharacterAttr.h"
#include "helmet.h"
#include <iostream>
using namespace std;

int main() {
	//create item
	/*Enhancement *enhancement = new Enhancement("str", 20);
	vector<Enhancement> influence;
	influence.push_back(*enhancement);
	Item test1("Helmet", influence, "Concordia Hat");
	Item test2("Boots", influence, "Concordia Hat");
	//create character
	CharacterAttr characterAttr(1,1,1,1,1,1);
	Fighter bruce(&characterAttr);
	bruce.setArmorClass(10);
	bruce.setHitPoint(10);
	cout << "Before equipping helmet: str = " <<bruce.getCharacterAttr()->getStrength()<< endl;
	//equip
	cout << "Equipping helmet" << endl;
	ItemContainer* equipment = new ItemContainer ();
	bruce.setCharacterEquipment(equipment);
	bruce.equipItem(test2);
	cout << "After equipping helmet: str = " << bruce.getCharacterAttr()->getStrength() << endl;
	//dequip
	cout << "Dequipping helmet" << endl;
	bruce.deEquipItem("Boots");
	cout << "After deequipping helmet: str = " << bruce.getCharacterAttr()->getStrength() << endl;
	//! Prompt close console
	int i = 1;
	while (i == 1) {
		cout << endl << "Enter 0 to quit the program." << endl;
		cin >> i;
	}
	*/
	
	CharacterAttr characterAttr(1, 1, 1, 1, 1, 1);
	Char *bruce = new Fighter(&characterAttr);
	bruce->setArmorClass(10);
	bruce->setHitPoint(10);

	ItemContainer* equipment = new ItemContainer();
	bruce->setCharacterEquipment(equipment);
	cout << " new strenght " << bruce->getCharacterAttr()->getStrength() << endl;
	bruce = new helmet(bruce);
	cout << " new strenght " << bruce->getCharacterAttr()->getStrength() << endl;
	
	


	system("pause");
	return 0;
}

