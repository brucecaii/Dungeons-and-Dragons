#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"
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
	json jsonInfluence;

	getInfluencesJson(jsonInfluence, item);

	jsonItem["item_type"] = item.getType();
	jsonItem["item_name"] = item.getName();
	jsonItem["enhancements"] = jsonInfluence;

	writeJsonFile << jsonItem;
	writeJsonFile.close();
}

//! Method to deserialize item from json object
//! @param filePath : file name of the serialized character
//! @param &item : item to deserialize
void ItemFileIO::readItem(string filePath, Item& item)
{
	ifstream readJsonFile(filePath, ifstream::in);
	json jsonItem(readJsonFile);

	vector<Enhancement> enhancements;
	auto enhancers = jsonItem["enhancements"];
	
	//retrieving enhancements 
	for (int j = 0; j < enhancers.size(); j++)
	{
		//Creating an enhancement vector
		auto currentEnhancement = enhancers.at(j);
		enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(),
			currentEnhancement["bonus"].get<int>()));
	}

	item.setName(jsonItem["item_name"]);
	item.setType(jsonItem["item_type"]);
	item.setEnhancements( enhancements );
}

//! Method to get JSON format of influences from an item
//! @param &influence : reference to json object
//! @param item : item to extract influences from
void ItemFileIO::getInfluencesJson(json& influence, Item item)
{
	auto enhancements = item.getInfluences();
	for (auto j = enhancements.begin(); j != enhancements.end(); j++)
	{
		json currentInfluence;
		currentInfluence["enhancement_type"] = j->getType();
		currentInfluence["bonus"] = j->getBonus();

		influence.push_back(currentInfluence);
	}
}
