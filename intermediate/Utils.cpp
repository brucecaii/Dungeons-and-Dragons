//! @file
//! @brief Implementation file for the Map class
//!
#include <algorithm>
#include <string>
#include <sstream>
#include <dirent.h>
#include <vector>
#include "Utils.h"

using std::getline;
using std::string;
using std::stringstream;
using std::vector;

//! Implementation of split, a utility function for splitting string with a delimiter and placing them in a vector
void Utils::split(const string &s, char delim, vector<string> &elems) {
  stringstream ss;
  ss.str(s);
  string item;
  while (getline(ss, item, delim)) {
      elems.push_back(item);
  }
}

vector<string> Utils::readCurrentDirectoryContents(string fileType) {
  vector<string> fileNames;

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

        fileNames.push_back(filename_stream.str());
      }
    }
  }
  return fileNames;
}

void Utils::removeSpaceCharFromString(string& str) {
  str.erase(std::remove (str.begin(), str.end(), ' '), str.end());
}

