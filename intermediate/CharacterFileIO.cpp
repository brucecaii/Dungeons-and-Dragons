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

//! saving character to a file in json format
void CharacterFileIO::saveCharacter(string filePath, Character ch)
{
	std::cout << "Saving Character..." << endl;
	ofstream writeJsonFile(filePath, ofstream::out);
	json character;

	//get character backpack and get backpack json
	auto backpack = ch.getBackpack();
	json backpackJson;
	getItemContainerJson( backpack, backpackJson);

	//get character inventory and get equiped items json
	auto equipment = ch.getEquipment();
	json equipmentJson;
	getItemContainerJson(equipment, equipmentJson);

	//Character attributes that are saved in json format
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

//! reading a character from a file in json format 
void CharacterFileIO::readCharacter(string filePath, Character& ch)
{
	ifstream readJsonFile(filePath, ifstream::in);
	json character(readJsonFile);

	// setting the values read from the file
	ch.setCharisma(int(character["charisma"]));
	ch.setStrength(int(character["strength"]));
	ch.setConstitution(int(character["constitution"]));
	ch.setIntelegence(int(character["intelligence"]));
	ch.setWisdom(int(character["wisdom"]));
	ch.setDexterity(int(character["dexterity"]));
	
	
	//Load his backpack items, but check if null first
	if (!character["backpack"].is_null())
	{
		loadBackpackItems(character, ch);
	}

	//Load his equipment items, but check if null first
	if (!character["equipment"].is_null())
	{
		loadEquipItems(character, ch);
	}
}

void CharacterFileIO::getItemContainerJson(ItemContainer* bp, json& bpJson)
{
	//Retrieve items from item container
	auto items = bp->getItems();

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
		bpJson.push_back(currentItem);
	}
}

//! retrieving backpack items
void CharacterFileIO::loadBackpackItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["backpack"];

	auto lol = backpack.at(0);

	for (int i = 0; i < backpack.size(); i++)
	{
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		for(int j = 0; j < enhancers.size() ; j++)
		{
			//Creating an enhancement vector
			auto currentEnhancement = enhancers.at(j);
			enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(), 
				currentEnhancement["bonus"].get<int>()));
		}

		ch.addItemBackpack(Item(temp["itemType"], enhancements, temp["itemName"]));
		enhancements.clear();
	}
}

//! retrieving items that are stored in the file
void CharacterFileIO::loadEquipItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["equipment"];

	auto lol = backpack.at(0);

	for (int i = 0; i < backpack.size(); i++)
	{
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		for (int j = 0; j < enhancers.size(); j++)
		{
			auto currentEnhancement = enhancers.at(j);
			enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(),
				currentEnhancement["bonus"].get<int>()));
		}

		ch.equipItem(Item(temp["itemType"], enhancements, temp["itemName"]));
		enhancements.clear();
	}
}
