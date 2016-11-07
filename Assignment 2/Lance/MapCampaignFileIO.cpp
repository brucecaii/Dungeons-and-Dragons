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
  map["mapWidth"] = GuiData::currentMapWidth;
  map["mapLength"] = GuiData::currentMapLength;
  map["placement"] = GuiData::currentMapString;
  writeJsonFile << map;
  writeJsonFile.close();
}

void MapCampaignFileIO::readMapJSON(string filePath) {
  ifstream readJsonFile(filePath, ifstream::in);
  json map(readJsonFile);
  GuiData::currentMapWidth = int(map["mapWidth"]);
  GuiData::currentMapLength = int(map["mapLength"]);
  GuiData::currentMapString = map["placement"];
  readJsonFile.close();
}

void MapCampaignFileIO::saveCampaignJSON(string filePath) {
  std::cout << "writing campaign" << std::endl;
  ofstream writeJsonFile(filePath, ofstream::out);
  json campaign(GuiData::currentCampaignMapOrder);
  writeJsonFile << campaign;
  writeJsonFile.close();
}

void MapCampaignFileIO::readCampaignJSON(string filePath) {
  ifstream readJsonFile(filePath, ifstream::in);
  json campaign(readJsonFile);
  GuiData::currentCampaignMapOrder = campaign.get<vector<string>>();
  readJsonFile.close();
}
