#include <fstream>
#include <iostream>
#include <sstream>
#include "CharacterFileIO.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using json = nlohmann::json;

//! saving character to a file in json format
void CharacterFileIO::saveCharacter(string filePath, Fighter ch)
{
	std::cout << "Saving Character..." << endl;
	ofstream writeJsonFile(filePath, ofstream::out);
	json character;

	//get character backpack and get backpack json
	auto backpack = ch.getCharacterBackpack();
	json backpackJson;
	getItemContainerJson( backpack, backpackJson);

	//get character inventory and get equiped items json
	auto equipment = ch.getCharacterEquipment();
	json equipmentJson;
	getItemContainerJson(equipment, equipmentJson);

	//Character attributes that are saved in json format
	character["strength"] = ch.getCharacterAttr()->getStrength();
	character["dexterity"] = ch.getCharacterAttr()->getDexterity();
	character["constitution"] = ch.getCharacterAttr()->getConstitution();
	character["intelligence"] = ch.getCharacterAttr()->getIntelligence();
	character["wisdom"] = ch.getCharacterAttr()->getWisdom();
	character["charisma"] = ch.getCharacterAttr()->getCharisma();
	character["backpack"] = backpackJson;
	character["equipment"] = equipmentJson;
	character["level"] = ch.getLevel();
	character["hitPoint"] = ch.getHitPoint();
	character["armorClass"] = ch.getArmorClass();
	character["attackBonus"] = ch.getAttackBonus();
	character["damageBonus"] = ch.getDamageBonus();
	character["currentPosition"] = ch.getCurrentPosition();
	character["mapType"] = ch.getTypeOnMap();
	character["fighterType"] = typeid(ch).name();
	character["playerType"] = ch.getPlayerType();

	writeJsonFile << character;
	writeJsonFile.close();
}

//! reading a character from a file in json format 
Fighter* CharacterFileIO::readCharacter(string filePath)
{
	ifstream readJsonFile(filePath, ifstream::in);
	json character(readJsonFile);

	Fighter *ch = new Fighter();
	// setting the values read from the file
	CharacterAttr *loadAttr = new CharacterAttr(
		character["intelligence"], 
		character["wisdom"], 
		character["strength"], 
		character["dexterity"], 
		character["constitution"], 
		character["charisma"]
	);
	if (character["fighterType"] == "Bully") ch = new Bully(loadAttr);
	if (character["fighterType"] == "Tank") ch = new Tank(loadAttr);
	if (character["fighterType"] == "Nimble") ch = new Nimble(loadAttr);
	ch->setCharacterAttr(loadAttr);
	ch->setLevel(character["level"]);
	ch->setHitPoint(character["hitPoint"]);
	ch->setArmorClass(character["armorClass"]);
	ch->setAttackBonus(character["attackBonus"]);
	ch->setDamageBonus(character["damageBonus"]);
	ch->setCurrentPosition(character["currentPosition"]);
	ch->setPlayerType(character["playerType"]);
	string str = character["mapType"];
	const char *cstr = str.c_str();
	ch->setTypeOnMap(*cstr);
	
	//Load his backpack items, but check if null first
	if (!character["backpack"].is_null())
	{
		loadBackpackItems(character, *ch);
	}

	//Load his equipment items, but check if null first
	if (!character["equipment"].is_null())
	{
		loadEquipItems(character, *ch);
	}

	return ch;
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

	for (size_t i = 0; i < backpack.size(); i++)
	{
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		for(size_t j = 0; j < enhancers.size() ; j++)
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

	for (size_t i = 0; i < backpack.size(); i++)
	{
		vector<Enhancement> enhancements;
		auto temp = backpack.at(i);
		auto enhancers = temp["enhancements"];

		for (size_t j = 0; j < enhancers.size(); j++)
		{
			auto currentEnhancement = enhancers.at(j);
			enhancements.push_back(Enhancement(currentEnhancement["enhancement_type"].get<string>(),
				currentEnhancement["bonus"].get<int>()));
		}

		ch.equipItem(Item(temp["itemType"], enhancements, temp["itemName"]));
		enhancements.clear();
	}
}
