//! @file
//! @brief Header file for the Map File IO class
//!
#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

//! Class implementing static functions involving Map File IO and Serialization
class MapCampaignFileIO {
  public:
    vector<string> readCurrentDirectoryContents(string fileType);
    void saveMapJSON(string filePath);
    void readMapJSON(string filePath);
    void saveCampaignJSON(string filePath);
    void readCampaignJSON(string filePath);
};


