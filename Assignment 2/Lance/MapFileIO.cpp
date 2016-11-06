//! @file
//! @brief Implementation file for the Map File IO class
//!
#include <vector>
#include <string>
#include <dirent.h>
#include <iostream>
#include <sstream>
#include "MapFileIO.h"
#include "Utils.h"

using std::string;
using std::stringstream;
using std::vector;

vector<string> MapFileIO::readDirectoryContents(string directory, string fileType) {
  vector<string> mapFileNames;
  char* directoryChar = const_cast<char*>(directory.c_str());

  DIR *dpdf;
  struct dirent *epdf;
  dpdf = opendir(directoryChar);

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

bool saveFileToDirectory(string filePath) {
  //

}


