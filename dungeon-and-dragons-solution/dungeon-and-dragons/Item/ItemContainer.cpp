//! @file 
//! @brief IMplementation file for the ItemContainer class  
//!

#include <iostream>
#include "ItemContainer.h"

using namespace std;

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
Item ItemContainer::getItemByType(string itemType)
{
	for (int i = 0; i < Items.size(); i++) {
		if (Items[i].getType() == itemType) 
			return Items[i];
	}
	Item notFound;
	return notFound;
}

//! method to return an item with a specific name contained in the ItemContainer
//! @param itemType : type of item to extract from the container
//! @return : item of the specified kind provided in input
Item ItemContainer::getItemByName(string itemName)
{
	for (int i = 0; i < Items.size(); i++) {
		if (Items[i].getName() == itemName) 
			return Items[i];
	}
	Item notFound;
	return notFound;
}

//!  deleting item by item name
void ItemContainer::deleteItem(string s) {
	
	for (int i = 0; i < Items.size(); i++){
		if (Items[i].getName() == s) {
			Items.erase(Items.begin()+i);
		}
	}
}

//! deleting item by type
void ItemContainer::deleteItemByType(string type) {
	for (int i = 0; i < Items.size(); i++){
		if (Items[i].getType() == type) {
			Items.erase(Items.begin()+i);
			}
	}
}

//! method returning size of item container 
int ItemContainer::getSize() {
	return this->Items.size();
}

//! method to display items inside a container to console
void ItemContainer::display()
{
	//Getting items from the container and printing it
	auto items = this->getItems();
	for (int i = 0; i < items.size(); i++)
	{
		//Printing item information
		cout << "=================================" << endl;
		cout << "Item name: " << items[i].getName() << endl;
		cout << "Item type: " << items[i].getType() << endl;

		//Printing item enhancement
		auto enhancement = items[i].getEnhancement();
		cout << enhancement.getType() << ": " << enhancement.getBonus() << endl;

		//formatting output
		cout << "=================================" << endl;
	}
}

//! construtor for backpack items container; creating items vector of max size 10
Backpack::Backpack() 
{
	Items = vector<Item>(10);
}

//! construtor for chest items container; creating items vector of max size 3
Chest::Chest()  
{
	Items = vector<Item>(3);
}

//! construtor for equipped items container; creating items vector of max size 6
EquipedItems::EquipedItems() 
{
	Items = vector<Item>(6);
}