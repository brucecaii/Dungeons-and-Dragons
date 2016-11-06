//! @file
//! @brief Header file for the Map File IO class
//!
#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

//! Class implementing static functions involving Map File IO and Serialization
class MapFileIO {
  public:
    vector<string> readDirectoryContents(string directory, string fileType);
};


