//! @file
//! @brief Implementation file for the Map File IO class
//!
#include <vector>
#include <string>
#include <fstream>
#include <dirent.h>
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


vector<string> MapCampaignFileIO::readCurrentDirectoryContents(string fileType) {
  vector<string> mapFileNames;

  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir(".");

  if (dpdf != NULL){
    while (epdf = readdir(dpdf)){
      string filename = epdf->d_name;

      vector<string> filename_split;
      Utils util;
      util.split(filename, '.', filename_split);

      if (fileType.compare(filename_split.back()) == 0) {
        filename_split.pop_back();

        stringstream filename_stream;
        for (size_t i = 0; i < filename_split.size(); ++i) {
          if (i != 0) {
            filename_stream << ".";
          }
          filename_stream << filename_split[i];
        }

        mapFileNames.push_back(filename_stream.str());
      }
    }
  }
  return mapFileNames;
}

void MapCampaignFileIO::saveMapJSON(string filePath) {
  std::cout << "writing map" << std::endl;
  ofstream writeJsonFile(filePath, ofstream::out);
  json map;
  int tempWidth = GameData::currentMapObject->getMapWidth();
  int tempLength = GameData::currentMapObject->getMapLength();
  string placement = "";
  vector<vector<char>> tempMap = GameData::currentMapObject->getMapData();
  for(int i = 0; i < tempWidth; i++) {
    for(int j = 0; j < tempLength; j++) {
      // Having issues with parsing some whitespace
      char tempChar = tempMap[i][j];
      if (tempChar != 'W' || tempChar != 'S' || tempChar != 'E' || tempChar != 'T' || tempChar != 'C' || tempChar != ' ') {
        tempChar = ' ';
      }
      placement += tempChar;
    }
  }
  std::cout << "placement: " << placement << std::endl;

  map["mapWidth"] = tempWidth;
  map["mapLength"] = tempLength;
  map["placement"] = placement;
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
