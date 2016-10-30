//! @file 
//! @brief Implementation file for the Item class  
//!

#include <iostream>
#include "Item.h"

using std::cout;

// constant representing number of item types
static const int NUMBER_ITEM_TYPES = 7;

// constants for maximum number of allowed enhancements for each item type
static const int MAX_HELMET_ENHANCEMENTS = 3;
static const int MAX_ARMOR_ENHANCEMENTS = 1;
static const int MAX_SHIELD_ENHANCEMENTS = 1;
static const int MAX_RING_ENHANCEMENTS = 5;
static const int MAX_BELT_ENHANCEMENTS = 2;
static const int MAX_BOOTS_ENHANCEMENTS = 2;
static const int MAX_WEAPON_ENHANCEMENTS = 2;

//! default constructor
Item::Item()
{
	type = "";
}

//! constructor that receives an item type as a string and a vector containing the enhancements that this item gives
//! @param type_name : string representing the type of item
//! @param influences : vector containing all the characteristics influenced by the item
Item::Item(string type_name, vector<Enhancement> influences)
{
	// ***todo***: this constructor should verify that an new item of a certain type only
	//check to see if item creation is of legal type
	if ( !(this->validateItemType(type_name)) )
	{
		cout << type_name << " is not a valid item type.";
		exit(1);
	}

	// enhances a character statistic valid for this item type
	type = type_name;
	influence = influences;
}

//! method to get the type of the item
//! @return : type of the item
string Item::getType()
{
	return type;
}

//! method to get the influences of the item
//! @return : vector containg the list of stats that the item enhances
vector<Enhancement> Item::getInfluences()
{
	return influence;
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
	string helmetEnhancements[MAX_HELMET_ENHANCEMENTS] = { "Intelligence", "Wisdom", "Armor Class" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for helmet, return false
	if (givenEnhancements.size() > MAX_HELMET_ENHANCEMENTS )
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to helmet
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++) 
		{
			// compare the current iteration with each allowed enchancement type for helmet
			if (i->getType().compare(helmetEnhancements[0]) || i->getType().compare(helmetEnhancements[1]) || i->getType().compare(helmetEnhancements[2]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a armor, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateArmor()
{
	// array containing the allowed types of enhancements for armor
	string armorEnhancements[MAX_HELMET_ENHANCEMENTS] = { "Armor Class" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for armor, return false
	if (givenEnhancements.size() > MAX_ARMOR_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to armor
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for armor
			if (i->getType().compare(armorEnhancements[0]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a shield, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateShield()
{
	// array containing the allowed types of enhancements for shield
	string shieldEnhancements[MAX_SHIELD_ENHANCEMENTS] = { "Armor Class" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for shield, return false
	if (givenEnhancements.size() > MAX_SHIELD_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to shield
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for shield
			if (i->getType().compare(shieldEnhancements[0]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a ring, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateRing()
{
	// array containing the allowed types of enhancements for ring
	string ringEnhancements[MAX_RING_ENHANCEMENTS] = { "Armor Class", "Strength", "Constitution", "Wisdom", "Charisma" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for ring, return false
	if (givenEnhancements.size() > MAX_RING_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to ring
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for ring
			if (i->getType().compare(ringEnhancements[0]) || i->getType().compare(ringEnhancements[1]) || i->getType().compare(ringEnhancements[2])
				|| i->getType().compare(ringEnhancements[3]) || i->getType().compare(ringEnhancements[4]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a belt, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateBelt()
{
	// array containing the allowed types of enhancements for belt
	string beltEnhancements[MAX_BELT_ENHANCEMENTS] = { "Constitution", "Strength" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for belt, return false
	if (givenEnhancements.size() > MAX_BELT_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to belt
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for belt
			if (i->getType().compare(beltEnhancements[0]) || i->getType().compare(beltEnhancements[1]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a boots, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateBoots()
{
	// array containing the allowed types of enhancements for boots
	string bootsEnhancements[MAX_BOOTS_ENHANCEMENTS] = { "Armor class", "Dexterity" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for boots, return false
	if (givenEnhancements.size() > MAX_BOOTS_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to boots
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for boots
			if (i->getType().compare(bootsEnhancements[0]) || i->getType().compare(bootsEnhancements[1]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}

//! method to validate a weapon, e.g verify that it contains only the allowed enhancements
//! @return : true if the item type contains only the enhancements allowed for its type according to the rules, false if not
bool Item::validateWeapon()
{
	// array containing the allowed types of enhancements for weapon
	string weaponEnhancements[MAX_WEAPON_ENHANCEMENTS] = { "Attack bonus", "Damange bonus" };
	vector<Enhancement> givenEnhancements = this->getInfluences();

	// if the given number of enhancements is greater than the maximum allowed number of enhancements for weapon, return false
	if (givenEnhancements.size() > MAX_WEAPON_ENHANCEMENTS)
	{
		return false;
	}
	else
	{
		// iterate to verify each enhancement given to weapon
		for (auto i = givenEnhancements.begin(); i != givenEnhancements.end(); i++)
		{
			// compare the current iteration with each allowed enchancement type for weapon
			if (i->getType().compare(weaponEnhancements[0]) || i->getType().compare(weaponEnhancements[1]))
			{
				continue;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}