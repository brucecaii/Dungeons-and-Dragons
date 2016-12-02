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
    // Basic method for outputting to screen
    sf::FloatRect drawText(sf::RenderWindow& w, string s, int charSize, const sf::Color& c, float posX, float posY);
    sf::FloatRect drawBox(sf::RenderWindow& w, float width, float height, const sf::Color& c, float posX, float posY);
    sf::FloatRect drawSprite(sf::RenderWindow& w, sf::Texture& t, float scaleX, float scaleY, float posX, float posY );

    // Utility methods that commonly used
    void drawHomeButton(sf::RenderWindow& window);
    void drawSaveButton(sf::RenderWindow& window);
    void drawValidationErrorIfNeeded(sf::RenderWindow& window);
    void drawMap(sf::RenderWindow& window);

    // Methods to draw scenes
    void isSelectingChoice(sf::RenderWindow& window);
    void isSelectingMapSize(sf::RenderWindow& window);
    void isTypingNameToCreate(sf::RenderWindow& window);
    void isChoosingSomethingToEditOrPlay(sf::RenderWindow& window);
    void isCreatingOrEditingMap(sf::RenderWindow& window);
    void isCreatingOrEditingCampaign(sf::RenderWindow& window);
    void isCreatingOrEditingCharacter(sf::RenderWindow& window);
    void isCreatingOrEditingItem(sf::RenderWindow& window);
    void isPlayingGame(sf::RenderWindow& window);

};
