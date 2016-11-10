//! @file 
//! @brief IMplementation file for the ItemContainer class  
//!

#include "ItemContainer.h"

//! default constructor
ItemContainer::ItemContainer()
{
	Items = vector<Item>();
}

//! constructor that takes a vector of items as input to create an ItemContainer
//! @param containeritems: vector of items to put in the new container
ItemContainer::ItemContainer( vector<Item> containeritems)
{
	Items = containeritems;
}

//! method to get the items of the container
//! @return : return the vector of items contained in the ItemContainer
vector<Item> ItemContainer::getItems()
{
	return Items;
}

//! method to add an item to the item container
//! @param anitem : new item to put in the ItemContainer
void ItemContainer::addItem(Item anitem)
{
	Items.push_back(anitem);
}

//! method to return the item of a certain type contained in the ItemContainer
//! assumption: the container can only contain one element of each type
//! @param itemType : type of item to extract from the container
//! @return : item of the specified kind provided in input
Item ItemContainer::getItem(string itemType)
{
	for (int i = 0; i < Items.size(); i++)
		if (Items[i].getType() == itemType)
			return Items[i];
}

void ItemContainer::deleteItem(string s) {
	
	for (int i = 0; i < Items.size(); i++){
		if (Items[i].getName() == s) {
			Items.erase(Items.begin()+i);
		}
	}
		
}

void ItemContainer::deleteItemByType(string type) {

	for (int i = 0; i < Items.size(); i++){
		if (Items[i].getType() == type) {
			Items.erase(Items.begin()+i);
		}
	}

}

int ItemContainer::getSize() {
	return this->Items.size();
}

Backpack::Backpack() //! construtor for backpack items container; creating items vector of max size 10
{
	Items = vector<Item>(10);
}

Chest::Chest()  //! construtor for chest items container; creating items vector of max size 3
{
	Items = vector<Item>(3);
}

EquipedItems::EquipedItems() //! construtor for equipped items container; creating items vector of max size 6
{
	Items = vector<Item>(6);
}