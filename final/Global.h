//! @file
//! @brief Header file for the Global namespace
//!
//! This file provides a global namespaces in order to access all characters currently playing the game from all classes.
//! This is required as most classes within this assignment, including all strategy pattern classes, require knowledge about other characters on the map.
//!

#include <vector>
#include "Character/Character.h"

//! This is a global namespaces in order to access all characters currently playing the game from all classes.
namespace Global {
  extern vector<Character> gameCharacters;
}

