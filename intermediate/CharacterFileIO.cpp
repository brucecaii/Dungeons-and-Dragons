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

void CharacterFileIO::saveCharacter(string  filePath, Character ch)
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

	//Character shits
	character["strength"] = ch.getStrength();
	character["dexterity"] = ch.getDexterity();
	character["constitution"] = ch.getConstitution();
	character["intelligence"] = ch.getIntelegence();
	character["wisdom"] = ch.getWisdom();
	character["charisma"] = ch.getCharisma();
	character["backpack"] = backpackJson;
	character["equipment"] = equipmentJson;

	writeJsonFile << character;
	writeJsonFile.close();
}

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

void CharacterFileIO::loadBackpackItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["backpack"];

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

void CharacterFileIO::loadEquipItems(json jsonText, Character& ch)
{
	//Retrieving enhancements
	auto backpack = jsonText["equipment"];

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
