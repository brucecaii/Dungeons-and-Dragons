//! @file
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
};





