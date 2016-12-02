#pragma once

#include <string>
#include <vector>
#include "../Character/Character.h"
#include "../Dependency/json.hpp"
#include "../Subject.h"

using std::string;
using std::vector;
using json = nlohmann::json;

class ItemFileIO : public Subject {

public:
	// method to serialize an item into json object
	void saveItem(string filePath, Item item);
	//method to deserialize an item from a json object
	Item *readItem(string filePath);

};