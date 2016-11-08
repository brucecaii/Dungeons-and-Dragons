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
    void drawNameConflictError(sf::RenderWindow& window);
    void drawHomeButton(sf::RenderWindow& window);
    void drawMapUi(sf::RenderWindow& window);
    void drawWidthIndicator(sf::RenderWindow& window);
    void drawWidthPlus(sf::RenderWindow& window);
    void drawWidthMinus(sf::RenderWindow& window);
    void drawLengthIndicator(sf::RenderWindow& window);
    void drawLengthPlus(sf::RenderWindow& window);
    void drawLengthMinus(sf::RenderWindow& window);
    void drawSaveButton(sf::RenderWindow& window);
    void drawWallSpriteSelector(sf::RenderWindow& window);
    void drawTreasureSpriteSelector(sf::RenderWindow& window);
    void drawExitSpriteSelector(sf::RenderWindow& window);
    void drawStartSpriteSelector(sf::RenderWindow& window);
    void drawCharacterSpriteSelector(sf::RenderWindow& window);
    void drawMonsterSpriteSelector(sf::RenderWindow& window);
};
