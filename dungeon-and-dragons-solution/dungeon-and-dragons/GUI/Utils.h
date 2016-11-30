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
    void split(const string &s, char delim, vector<string> &elems);
    vector<string> readCurrentDirectoryContents(string fileType);
    void removeSpaceCharFromString(string& str);
};



