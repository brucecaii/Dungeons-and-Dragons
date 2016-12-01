
//! @brief Header file for the Events class
//!
#pragma once

#include <SFML/Graphics.hpp>
#include "../Subject.h"

//! Class implementing event-related static functions
class Events : public Subject {
  public:
    void respondToSelectionBoxClick(sf::RenderWindow& window);
    void respondToFileSelectionClick(sf::RenderWindow& window);
    void respondToRealTimeTypeFeedback(sf::Event& evt);
    void respondToHomeButtonClick(sf::RenderWindow& window);
    void respondToSaveMapCampaign(sf::RenderWindow& window);
    void respondToMapSizeClick(sf::RenderWindow& window);
    void respondToMapCreateOkButton(sf::RenderWindow& window);
    void respondToMapTileSelect(sf::RenderWindow& window);
    void respondToMapBoxClick(sf::RenderWindow& window);
    void respondToCampaignAvailableMapsClick(sf::RenderWindow& window);
    void respondToCampaignMapOrderClick(sf::RenderWindow& window);
    void respondToPlayingGameEvents(sf::RenderWindow& window);

};





