#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"
#include "CharacterFileIO.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using json = nlohmann::json;


//! Method to serialize character into json object
//! @param filePath : file name of the serialized character
//! @param ch : character to serialize
void CharacterFileIO::saveCharacter(string filePath, Character ch)
{
	std::cout << "Saving Character..." << endl;
	ofstream writeJsonFile(filePath, ofstream::out);
	json character;

	//get character backpack and get backpack json
	auto backpack = ch.getBackpack();
	json backpackJson;
	getItemContainerJson(backpack, backpackJson);

	//get character inventory and get equiped items json
	auto equipment = ch.getEquipment();
	json equipmentJson;
	getItemContainerJson(equipment, equipmentJson);

	//Character shits
	character["strength"] = ch.getStrengthFromBase();
	character["dexterity"] = ch.getDexterityFromBase();
	character["constitution"] = ch.getConstitutionFromBase();
	character["intelligence"] = ch.getIntelegenceFromBase();
	character["wisdom"] = ch.getWisdomFromBase();
	character["charisma"] = ch.getCharismaFromBase();
	character["backpack"] = backpackJson;
	character["equipment"] = equipmentJson;

	writeJsonFile << character;
	writeJsonFile.close();
}

//! Method to deserialize character from json object
//! @param filePath : file name of the serialized character
//! @param &ch : character to deserialize 
void CharacterFileIO::readCharacter(string filePath, Character& ch)
{
	ifstream readJsonFile(filePath, ifstream::in);
	json character(readJsonFile);

	ch.setCharisma(int(character["charisma"]));
	ch.setStrength(int(character["strength"]));
	ch.setConstitution(int(character["constitution"]));
	ch.setIntelegence(int(character["intelligence"]));
	ch.setWisdom(int(character["wisdom"]));
	ch.setDexterity(int(character["dexterity"]));
	//ch.setLevel(int(character["level"]));

	//Load his backpack items
	loadBackpackItems(character, ch);
	loadEquipItems(character, ch);
	ch.updatestats();
}

//! Method to retrieve JSON of the character's backpack or equiped items
//! @param it : the item container of which you want the json of
//! @param &itJson : reference to a json object
void CharacterFileIO::getItemContainerJson(ItemContainer* it, json& itJson)
{
	//Retrieve items from item container
	auto items = it->getItems();

	//Retrieve enhancement type and bonus from each item
	for (auto i = items.begin(); i != items.end(); i++)
	{
		//json wrapping the current item
		json currentItem;

		//Get influences
		json influences;

		auto currentInfluences = i->getInfluences();

		for (auto j = currentInfluences.begin(); j != currentInfluences.end(); j++)
		{
			json currentInfluence;
			currentInfluence["enhancement_type"] = j->getType();
			currentInfluence["bonus"] = j->getBonus();

			influences.push_back(currentInfluence);
		}

		//Get item name and type
		currentItem["itemName"] = i->getName();
		currentItem["itemType"] = i->getType();
		currentItem["enhancements"] = influences;

		//add to main
		itJson.push_back(currentItem);
	}
}

//! Method to deserialize a json into a backpack
//! @param json : json to deserialize into a backpack
//! @param &ch : reference to a character 
void CharacterFileIO::loadBackpackItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["backpack"];

	for (int i = 0; i < backpack.size(); i++)
	{
		//Retrieve enhancement at index i
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		// looping through each enhancement in the enhancement list
		for (int j = 0; j < enhancers.size(); j++)
		{
			//Creating an enhancement vector
			auto currentEnhancement = enhancers.at(j);
			enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(),
				currentEnhancement["bonus"].get<int>()));
		}

		//Creating the item and adding it to the character's backpack
		ch.addItemBackpack(Item(temp["itemType"], enhancements, temp["itemName"]));
		enhancements.clear();
	}
}

//! Method to deserialize a json into equiped items
//! @param json : json to deserialize into equiped items
//! @param &ch : reference to a character 
void CharacterFileIO::loadEquipItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["equipment"];

	//Retrieve enhancement at index i
	for (int i = 0; i < backpack.size(); i++)
	{
		//Retrieve enhancement at index i
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		// looping through each enhancement in the enhancement list
		for (int j = 0; j < enhancers.size(); j++)
		{
			auto currentEnhancement = enhancers.at(j);
			enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(),
				currentEnhancement["bonus"].get<int>()));
		}

		//Creating the item and equipping it to the character
		ch.equipItem(Item(temp["itemType"], enhancements, temp["itemName"]));
		enhancements.clear();
	}
}