//! @file
//! @brief Header file for the Utils class
//!
#pragma once
#include <string>
#include <vector>

using std::string;
using std::vector;

//! Class implementing utility functions
class Utils {
  public:
    vector<string> splitBySpace(string source);
    vector<string> split(const string &text, char sep);
    vector<string> readCurrentDirectoryContents(string fileType);
    void removeSpaceCharFromString(string& str);
};



