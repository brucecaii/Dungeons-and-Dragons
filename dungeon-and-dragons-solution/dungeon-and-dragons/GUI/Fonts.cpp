#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Fonts.h"

using std::cerr;
using std::endl;

sf::Font Fonts::generateFont(string fontPath) {
  sf::Font currentFont;
  if (!currentFont.loadFromFile(fontPath)) {
    cerr << "Error loading font. System exiting" << endl;
    exit(1);
  }
  return currentFont;
}
