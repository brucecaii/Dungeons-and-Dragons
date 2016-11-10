#pragma once

#include <string>
#include <vector>
#include "Character.h"

using std::string;
using std::vector;
using json = nlohmann::json;

class CharacterFileIO {

public:
	void saveCharacter(string filePath, Character ch);
	void readCharacter(string filePath, Character& ch);

	void getItemContainerJson( ItemContainer* bp, json& bpJson );
	void loadBackpackItems(json jsonText, Character& ch);
	void loadEquipItems(json jsonText, Character& ch);
};