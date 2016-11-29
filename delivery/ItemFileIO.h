#pragma once

#include <string>
#include <vector>
#include "Character.h"

using std::string;
using std::vector;
using json = nlohmann::json;

class ItemFileIO {

public:
	// method to serialize an item into json object
	void saveItem(string filePath, Item item);
	//method to deserialize an item from a json object
	void readItem(string filePath, Item& item);
	//get influences json from an item, needed to create an item when deserializing
	void getInfluencesJson(json& influence, Item item);
};