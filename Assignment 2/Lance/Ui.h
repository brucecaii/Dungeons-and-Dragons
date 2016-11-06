//! @file
//! @brief Header file for the Ui class
//!
#pragma once

#include <string>
#include <vector>
#include "SFML/Graphics.hpp"

using std::string;
using std::vector;

//! Class implementing ui-related functions
class Ui {
  public:
    void updateTime();
    void drawEllipsis(sf::RenderWindow& window);
    void drawGreetings(sf::RenderWindow& window);
    void drawCallToAction(sf::RenderWindow& window);
    void drawSelectionBoxes(sf::RenderWindow& window, sf::RectangleShape& selectionBox);
    void drawSelectMapCampaign(sf::RenderWindow& window);
    void drawTypeMapCampaignName(sf::RenderWindow& window);
    void drawSelectFileNames(sf::RenderWindow& window, vector<string> current_files);
    void drawRealTimeTypeFeedback(sf::RenderWindow& window);
};
