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
//! @brief Header file for the ItemContainer class  
//!

#ifndef ItemContainer_h
#define ItemContainer_h

#include <string>
#include<vector>
using namespace std;
#include "Item.h"

//! Class that implements an item container
class ItemContainer
{
	public:
		// Default constructor
		ItemContainer();
		// Constructor
		ItemContainer(vector<Item> items);
		// method to get the items of the container
		vector<Item> getItems();
		// method to add an item to the item container
		void addItem(Item anitem);
		// method to get an item from the item container
		Item getItem(string itemType);
		//! method to delete an item
		void deleteItem(string name); //! take name of item to delete
		void deleteItemByType(string type);
		//! method to get size of container
		int getSize();
		//! method to display items in container
		void display();
	private:
		vector<Item> Items;
};

//! Default constructor for backpack
class Backpack : public  ItemContainer {
	public : 
		 Backpack();
	private :
		vector<Item> Items;
};

//! Default constructor for chest
class Chest : public  ItemContainer {
	public:
		Chest();
	private:
		vector<Item> Items;
};

//! Default constructor for EquipedItems
class EquipedItems : public  ItemContainer {
	public:
		EquipedItems();
	private:
		vector<Item> Items;
};

#endif



