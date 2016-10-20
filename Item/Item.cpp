//! @file 
//! @brief Implementation file for the Item class  
//!

#include "Item.h"

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
	// ***todo***
	return true;
}
