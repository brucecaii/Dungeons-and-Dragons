
//! @brief Header file for the Events class
//!
#pragma once

#include <SFML/Graphics.hpp>

//! Class implementing event-related static functions
class Events {
  public:
    void respondToSelectionBoxClick(sf::RenderWindow& window);
    void respondToFileSelectionClick(sf::RenderWindow& window);
    void respondToRealTimeTypeFeedback(sf::Event& evt);
    void respondToHomeButtonClick(sf::RenderWindow& window);
    void respondToSaveMapCampaign(sf::RenderWindow& window);
    void respondToWidthPlusClick(sf::RenderWindow& window);
    void respondToWidthMinusClick(sf::RenderWindow& window);
    void respondToLengthPlusClick(sf::RenderWindow& window);
    void respondToLengthMinusClick(sf::RenderWindow& window);
    void respondToMapCreateOkButton(sf::RenderWindow& window);
    void respondToMapTileWallSelect(sf::RenderWindow& window);
    void respondToMapTileMonsterSelect(sf::RenderWindow& window);
    void respondToMapTileStartSelect(sf::RenderWindow& window);
    void respondToMapTileExitSelect(sf::RenderWindow& window);
    void respondToMapTileTreasureSelect(sf::RenderWindow& window);
    void respondToMapTileEmptySelect(sf::RenderWindow& window);
};





