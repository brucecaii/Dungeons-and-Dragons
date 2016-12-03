//! @file
//! @brief Implementation file for the Map class
//!
#include <algorithm>
#include <string>
#include <sstream>
#include "dirent.h"
#include <vector>
#include "Utils.h"

using std::getline;
using std::string;
using std::stringstream;
using std::vector;

//! Implementation of split, a utility function for splitting string with a delimiter and placing them in a vector
std::vector<std::string> Utils::splitBySpace(std::string source) {
    string buf; // Have a buffer string
    stringstream ss(source); // Insert the string into a stream

    vector<string> tokens; // Create vector to hold our words

    while (ss >> buf)
        tokens.push_back(buf);
    return tokens;
}

std::vector<std::string> Utils::split(const std::string &text, char sep) {
  std::vector<std::string> tokens;
  std::size_t start = 0, end = 0;
  while ((end = text.find(sep, start)) != std::string::npos) {
    tokens.push_back(text.substr(start, end - start));
    start = end + 1;
  }
  tokens.push_back(text.substr(start));
  return tokens;
}

vector<string> Utils::readCurrentDirectoryContents(string fileType) {
  vector<string> fileNames;

  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir(".");

  if (dpdf != NULL){
    while (epdf = readdir(dpdf)){
      string filename = epdf->d_name;

      Utils util;
      vector<string> filename_split = util.split(filename, '.');

      if (fileType.compare(filename_split.back()) == 0) {
        filename_split.pop_back();

        stringstream filename_stream;
        for (size_t i = 0; i < filename_split.size(); ++i) {
          if (i != 0) {
            filename_stream << ".";
          }
          filename_stream << filename_split[i];
        }

        fileNames.push_back(filename_stream.str());
      }
    }
  }
  return fileNames;
}

void Utils::removeSpaceCharFromString(string& str) {
  str.erase(std::remove (str.begin(), str.end(), ' '), str.end());
}

