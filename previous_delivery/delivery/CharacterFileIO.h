#pragma once

#include <string>
#include <vector>
#include "Character.h"

using std::string;
using std::vector;
using json = nlohmann::json;

class CharacterFileIO {

public:
	// method to serialize a character into json object
	void saveCharacter(string filePath, Character ch);
	//method to deserialize a character from a json object
	void readCharacter(string filePath, Character& ch);
	// method used to obtain json format of an item container
	void getItemContainerJson( ItemContainer* bp, json& bpJson );
	//deserialize backpack from a json object
	void loadBackpackItems(json jsonText, Character& ch);
	//deserialize equiped items from a json object
	void loadEquipItems(json jsonText, Character& ch);
};