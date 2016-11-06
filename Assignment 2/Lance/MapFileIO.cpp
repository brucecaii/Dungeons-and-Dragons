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



//! Implementation of is beside, checks if a specific cell is adjacent (top/left/bottom/right) to a specific cell type.
//! @param x: an integer value of horizontal index of the map's grid
//! @param y: an integer value of vertical index of the map's grid
//! @return bool value, true if there is a the cell type adjacent to the specific cell chosen
//bool Map::isBeside(int x, int y, char type) {
  //bool bIsBeside= false;
  //if (x > 0) {
    //if (map[x-1][y] == type) {
      //bIsBeside= true;
    //}
  //}
  //if (x < mapWidth-1) {
    //if (map[x+1][y] == type) {
      //bIsBeside= true;
    //}
  //}
  //if (y > 0) {
    //if (map[x][y-1] == type) {
      //bIsBeside= true;
    //}
  //}
  //if (y< mapLength-1) {
    //if (map[x][y+1] == type) {
      //bIsBeside= true;
    //}
  //}

  //return bIsBeside;
//}

