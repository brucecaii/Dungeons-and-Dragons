//! (1) In Dungeons and Dragons, the rules for Items and Item container are as follow
//!		First of all, there are seven (7) item types (Helmet, Armor, Shield, Ring, Belt, Boots, Weapon).
//!		Each of these item types have their OWN respective and allowed enhancements. For example, a helmet can ONLY have enhancements (Intelligence, Wisdom and Armor class)
//!     There are nine (9) types of enhancements (Intelligence, Wisdom, Armor class, Strength, Constitution, Charisma, Dexterity, Attack bonus and Damage bonus)
//!		Moreover, to be a valid enhancement, bonuses must be between +1 and +5. 
//!     Finally, we have the item container. The item container contains items. 
//!		As the iteration of this project grows, there will eventually have a character backpack, character worn items and chests.
//!     
//! (2) For the items and item container part of the project, three (3) main classes are necessary: Enhancement, Item and ItemContainer.
//!		Item container is a class containing a vector of type items. Item container contains three (3) methods: getItems() to get all items, getItem(itemType) to get a specific item and addItem(item) to add an item.
//!		Item is a class containing attribute influence (a vector of enhancements) and item_type (a string named after the item type). 
//!     In Item, there is getType() to get the item type, getInfluences() to get the vector of enhancement, validateItem() to validate whether the item is legal according to game rules.
//!		validateItemType(string type) to validate whether the item being created is legal according to game rules or not (ex: we cannot create a bow or spear). This method is used on the constructor as a check. Exit(1) if illegal item is made.
//!     validateHelmet(), validateArmor(), validateShield(), validateRing(), validateBelt(), validateBoots(), validateWeapon() to validate that the respective item only contains 
//!     allowed enhancements to their respective type according to game rules (ex: helmet can only have intelligence, armor and wisdom). This is used by method validateItem() and calls the right item method based on the item type.
//!     Finally, Enhancement is a class containing type (string) and bonus (int) attributes. Methods include: getType() to get the type of enhancement it is, getBonus() to get the bonus for that enhancement
//!     and validateBonus() to make sure that the given enhancement respect the game rules (1-5, nothing less, nothing more).
//!
//! (3) No libraries have been used for this project, yet.		
//!
//! @file 
//! @brief Header file for the Item class  
//!
#ifndef Item_h
#define Item_h

#include <string>
#include<vector>
#include "Enhancement.h"
using namespace std;

//! class for the implementation of items wearable by a character
class Item
{
public:


	Item(string type, Enhancement e, string name); // used for debugging, ignore
	// Default constructor
	Item();
	// Constructor
	Item(string type,vector<Enhancement> influences , string name);
	// method to get the type of the item
	string getType();
	// method to get name
	string getName();
	// method to get the influences of the item
	vector<Enhancement> getInfluences();
	//method to validate an item
	bool validateItem();
	//method to validate item type
	bool validateItemType(string type);
	//method to validate a helmet
	bool validateHelmet();
	//method to validate an armor
	bool validateArmor();
	//method to validate a shield
	bool validateShield();
	//method to validate a ring
	bool validateRing();
	//method to validate a belt
	bool validateBelt();
	//method to validate boots
	bool validateBoots();
	//method to validate a weapon
	bool validateWeapon();
private:
	string type;
	vector<Enhancement> influence;
	string name;
};
#endif

