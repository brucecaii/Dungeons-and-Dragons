#pragma once

#include <string>
#include <vector>
#include "Character.h"

using std::string;
using std::vector;
using json = nlohmann::json;

class ItemFileIO {

public:
	void saveItem(string filePath, Item item);
	void readItem(string filePath, Item& item);

	void getInfluencesJson(json& influence, Item item);
};