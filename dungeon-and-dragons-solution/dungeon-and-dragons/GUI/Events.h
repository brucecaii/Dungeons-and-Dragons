
//! @brief Header file for the Events class
//!
#pragma once

#include <SFML/Graphics.hpp>
#include "../Subject.h"

//! Class implementing event-related static functions
class Events : public Subject {
  public:
    void respondToSelectionBoxClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToFileSelectionClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToRealTimeTypeFeedback(sf::Event& evt);
    void respondToHomeButtonClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToSaveMapCampaign(sf::RenderWindow& window, sf::Event& evt);
    void respondToMapSizeClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToMapCreateOkButton(sf::RenderWindow& window, sf::Event& evt);
    void respondToMapTileSelect(sf::RenderWindow& window, sf::Event& evt);
    void respondToMapBoxClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToCampaignAvailableMapsClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToCampaignMapOrderClick(sf::RenderWindow& window, sf::Event& evt);
    void respondToPlayingGameEvents(sf::RenderWindow& window, sf::Event& evt);
    void loadCharactersOnNewMap();
};





