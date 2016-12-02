//! @file
//! @brief Implementation file for the Item class
//!

#include <iostream>
#include "Item.h"

using std::cout;

// constant representing number of item types
static const int NUMBER_ITEM_TYPES = 7;

//! default constructor
Item::Item()
{
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, Enhancement enhancement, string nameofitem)
{
	name = nameofitem;
	
	// ***todo***: this constructor should verify that an new item of a certain type only
	//check to see if item creation is of legal type
	if ( !(this->validateItemType(type_name)) )
	{
		cout << type_name << " is not a valid item type.";
		exit(1);
	}

	// enhances a character statistic valid for this item type
	type = type_name;
	this->enhancement = enhancement;
}

//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return type;
}

//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
Enhancement Item::getEnhancement()
{
	return this->enhancement;
}

//! method to validate an item, e.g. verify that an new item of a certain type only enhances a character statistic valid for this item type
//! @return : true if the enhancement list is valid according to the rules, false if not
bool Item::validateItem()
{	
	if (this->getType() == "Helmet")
	{
		return this->validateHelmet();
	} 
	else if (this->getType() == "Armor")
	{
		return this->validateArmor();
	}
	else if (this->getType() == "Shield")
	{
		return this->validateShield();
	}
	else if (this->getType() == "Ring")
	{
		return this->validateRing();
	}
	else if (this->getType() == "Belt")
	{
		return this->validateBelt();
	}
	else if (this->getType() == "Boots")
	{
		return this->validateBoots();
	}
	else if (this->getType() == "Weapon")
	{
		return this->validateWeapon();
	}
	return false;
}

//! method to validate an item type, e.g. verify that the type is legal (helmet, armor, shield...etc.)
//! @return : true if the item type is valid according to the rules, false if not
bool Item::validateItemType(string type)
{
	// array containing the 7 type of items
	string typeList[NUMBER_ITEM_TYPES] = { "Helmet", "Armor", "Shield", "Ring", "Belt", "Boots", "Weapon" };

	// looping through typeList to find a corresponding match to the passed item type
	for (int i = 0; i < NUMBER_ITEM_TYPES; i++)
	{
		if (typeList[i].compare(type) == 0)
		{
			return true;
		}
	}

	return false;
}

//! method to validate a helmet, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateHelmet()
{
	// array containing the allowed types of enhancements for helmet
	string helmetEnhancements[3] = { "Intelligence", "Wisdom", "Armor Class" };
	Enhancement givenEnhancements = this->getEnhancement();

	// compare the current iteration with each allowed enchancement type for helmet
	if (givenEnhancements.getType().compare(helmetEnhancements[0]) || 
		givenEnhancements.getType().compare(helmetEnhancements[1]) || 
		givenEnhancements.getType().compare(helmetEnhancements[2])) {
				return true;
	}
	return true;
}

//! method to validate a armor, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateArmor()
{
	// array containing the allowed types of enhancements for armor
	string armorEnhancements[1] = { "Armor Class" };
	Enhancement givenEnhancements = this->getEnhancement();

	if (givenEnhancements.getType().compare(armorEnhancements[0])) {
		return true;
	}
	return true;
}

//! method to validate a shield, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateShield()
{
	// array containing the allowed types of enhancements for shield
	string shieldEnhancements[1] = { "Armor Class" };
	Enhancement givenEnhancements = this->getEnhancement();

	if (givenEnhancements.getType().compare(shieldEnhancements[0])) {
		return true;
	}
	return true;
}

//! method to validate a ring, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateRing()
{
	// array containing the allowed types of enhancements for ring
	string ringEnhancements[5] = { "Armor Class", "Strength", "Constitution", "Wisdom", "Charisma" };
	Enhancement givenEnhancements = this->getEnhancement();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for ring, return false
	if (givenEnhancements.getType().compare(ringEnhancements[0]) ||
		givenEnhancements.getType().compare(ringEnhancements[1]) ||
		givenEnhancements.getType().compare(ringEnhancements[2]) ||
		givenEnhancements.getType().compare(ringEnhancements[3]) || 
		givenEnhancements.getType().compare(ringEnhancements[4])) {
		return true;
	}
	return true;
}

//! method to validate a belt, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateBelt()
{
	// array containing the allowed types of enhancements for belt
	string beltEnhancements[2] = { "Constitution", "Strength" };
	Enhancement givenEnhancements = this->getEnhancement();

	if (givenEnhancements.getType().compare(beltEnhancements[0]) ||
		givenEnhancements.getType().compare(beltEnhancements[1])) {
		return true;
	}
	return true;
}

//! method to validate a boots, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateBoots()
{
	// array containing the allowed types of enhancements for boots
	string bootsEnhancements[2] = { "Armor class", "Dexterity" };
	Enhancement givenEnhancements = this->getEnhancement();

	if (givenEnhancements.getType().compare(bootsEnhancements[0]) ||
		givenEnhancements.getType().compare(bootsEnhancements[1])) {
		return true;
	}
	return true;
}

//! method to validate a weapon, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateWeapon()
{
	// array containing the allowed types of enhancements for weapon
	string weaponEnhancements[2] = { "Attack bonus", "Damange bonus" };
	Enhancement givenEnhancements = this->getEnhancement();

	if (givenEnhancements.getType().compare(weaponEnhancements[0]) ||
		givenEnhancements.getType().compare(weaponEnhancements[1])) {
		return true;
	}
	return true;
}

//! method to get name of the item
//! @return : name of the item
string Item::getName(){
	return name;
}

//! method to set name of item
//! @param item_name : string representing the name of item
void Item::setName(string item_name)
{
	this->name = item_name;
}

//! method to set type of item
//! @param type_name : string representing the type of item
void Item::setType(string type_name)
{
	this->type = type_name;
}

//! method to set enhancements of an item
//! @param type_name : vector representing the enhancements of the item
void Item::setEnhancement(Enhancement enhancements)
{
	this->enhancement = enhancements;
}
