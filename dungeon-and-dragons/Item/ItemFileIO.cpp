#include <fstream>
#include <iostream>
#include <sstream>
#include "ItemFileIO.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using json = nlohmann::json;

//! Method to serialize character into json object
//! @param filePath : file name of the serialized character
//! @param item : item to serialize
void ItemFileIO::saveItem(string filePath, Item item)
{
	std::cout << "Saving Item..." << endl;
	ofstream writeJsonFile(filePath, ofstream::out);
	json jsonItem;

	jsonItem["item_type"] = item.getType();
	jsonItem["item_name"] = item.getName();
	jsonItem["enhancementType"] = item.getEnhancement().getType();
	jsonItem["enhancementBonus"] = item.getEnhancement().getBonus();

	writeJsonFile << jsonItem;
	writeJsonFile.close();
}

//! Method to deserialize item from json object
//! @param filePath : file name of the serialized character
//! @param &item : item to deserialize
Item* ItemFileIO::readItem(string filePath)
{
	ifstream readJsonFile(filePath, ifstream::in);
	Item *loadedItem = new Item();
	if (readJsonFile.is_open())
	{
		json jsonItem(readJsonFile);
		Enhancement *enhancement = new Enhancement(jsonItem["enhancementType"], jsonItem["enhancementBonus"]);
		loadedItem->setName(jsonItem["item_name"]);
		loadedItem->setType(jsonItem["item_type"]);
		loadedItem->setEnhancement(*enhancement);
	}
	readJsonFile.close();
	return loadedItem;
}
