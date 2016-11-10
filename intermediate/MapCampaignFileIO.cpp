//! @file
//! @brief Implementation file for the Map File IO class
//!
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "json.hpp"
#include "MapCampaignFileIO.h"
#include "Utils.h"
#include "GuiData.h"
#include "GameData.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;
using std::vector;
using json = nlohmann::json;



void MapCampaignFileIO::saveMapJSON(string filePath) {
  std::cout << "writing map" << std::endl;
  ofstream writeJsonFile(filePath, ofstream::out);
  json map;
  map["mapWidth"] = GameData::currentMapObject->getMapWidth();
  map["mapLength"] = GameData::currentMapObject->getMapLength();
  map["placement"] = GameData::currentMapObject->getMapData();
  writeJsonFile << map;
  writeJsonFile.close();
}

void MapCampaignFileIO::readMapJSON(string filePath) {
  ifstream readJsonFile(filePath, ifstream::in);
  json map(readJsonFile);
  int tempWidth = int(map["mapWidth"]);
  int tempLength = int(map["mapLength"]);
  string placement = map["placement"];
  delete GameData::currentMapObject;
  GameData::currentMapObject = new Map(tempWidth, tempLength, placement);
  readJsonFile.close();
}

void MapCampaignFileIO::saveCampaignJSON(string filePath) {
  std::cout << "writing campaign" << std::endl;
  ofstream writeJsonFile(filePath, ofstream::out);
  json campaign(GameData::currentCampaignObject->getCampaignMapOrder());
  writeJsonFile << campaign;
  writeJsonFile.close();
}

void MapCampaignFileIO::readCampaignJSON(string filePath) {
  ifstream readJsonFile(filePath, ifstream::in);
  json campaign(readJsonFile);
  GameData::currentCampaignObject->setCampaignMapOrder(campaign.get<vector<string>>());
  readJsonFile.close();
}
