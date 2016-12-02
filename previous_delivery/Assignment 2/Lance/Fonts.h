//! @file
//! @brief Implementation file for the Fonts class
//!
#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using std::string;

//! Class implementing a utility for setting the font
class Fonts {
  public:
    sf::Font generateFont(string fontPath);
};


