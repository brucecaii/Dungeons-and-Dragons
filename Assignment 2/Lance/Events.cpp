//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiData.h"
#include "Events.h"
#include "MapFileIO.h"

using std::cout;
using std::endl;

void Events::respondToSelectionBoxClick(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::SELECTION_BOXES_APPEAR_TIME && GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      MapFileIO mapSerializer;
      if (GuiData::createMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readDirectoryContents("./maps", "map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToCreate = true;

      }
      if (GuiData::editMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readDirectoryContents("./maps", "map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToEdit = true;
      }
      if (GuiData::createCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readDirectoryContents("./campaigns", "campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToCreate = true;
      }
      if (GuiData::editCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readDirectoryContents("./campaigns", "campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToEdit = true;
      }
    }
  }
}

void Events::respondToFileSelectionClick(sf::RenderWindow& window) {
  if (GuiData::isChoosingMapToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_map_positions.size(); i++) {
        if (GuiData::current_map_positions[i].contains(mousePosition)) {
          GuiData::isChoosingMapToEdit = false;
          GuiData::isEditingMap = true;
          GuiData::chosenMap = GuiData::current_maps[i];
        }
      }
    }
  }

  if (GuiData::isChoosingCampaignToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_campaign_positions.size(); i++) {
        if (GuiData::current_campaign_positions[i].contains(mousePosition)) {
          GuiData::isChoosingCampaignToEdit = false;
          GuiData::isEditingCampaign = true;
          GuiData::chosenCampaign = GuiData::current_campaigns[i];
        }
      }
    }
  }
}

void Events::respondToRealTimeTypeFeedback(sf::Event& evt) {
    if (evt.type == sf::Event::TextEntered) {
      cout << evt.text.unicode << endl;
        if (GuiData::isChoosingMapToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_maps.size(); i++) {
              if (GuiData::current_maps[i] == GuiData::createdMap) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::isChoosingMapToCreate = false;
              GuiData::isEditingMap = true;
              // save map to file here /json once created.
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
              GuiData::createdMap.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdMap += evt.text.unicode;
          }
        }
        if (GuiData::isChoosingCampaignToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_campaigns.size(); i++) {
              if (GuiData::current_campaigns[i] == GuiData::createdCampaign) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::isChoosingCampaignToCreate = false;
              GuiData::isEditingCampaign = true;
              // save map to file here /json once created.
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
              GuiData::createdMap.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdMap += evt.text.unicode;
          }
        }
    }
}

void Events::respondToHomeButtonClick(sf::RenderWindow& window) {
  if (!GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::HomeButton.getGlobalBounds().contains(mousePosition)) {
        GuiData::hasCreateMapPosition = false;
        GuiData::hasEditMapPosition = false;
        GuiData::hasCreateCampaignPosition = false;
        GuiData::hasEditCampaignPosition = false;
        GuiData::isSelectingChoice = true;
        GuiData::isChoosingMapToCreate = false;
        GuiData::isChoosingMapToEdit = false;
        GuiData::isChoosingCampaignToCreate = false;
        GuiData::isChoosingCampaignToEdit = false;
        GuiData::isEditingCampaign = false;
        GuiData::isEditingMap = false;
        GuiData::shouldShowNameConflictError = false;
      }
    }
  }
}

      //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        //shape.move(0.0f, -0.1f);
      //}
      //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        //shape.move(0.0f, 0.1f);
      //}
      //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        //shape.move(-0.1f, 0.0f);
      //}
      //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
         //shape.move(0.1f, 0.0f);
      //}
