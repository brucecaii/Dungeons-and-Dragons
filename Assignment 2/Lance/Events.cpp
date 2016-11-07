//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GuiData.h"
#include "Events.h"
#include "MapCampaignFileIO.h"

void Events::respondToSelectionBoxClick(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::SELECTION_BOXES_APPEAR_TIME && GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      MapCampaignFileIO mapSerializer;
      if (GuiData::createMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToCreate = true;

      }
      if (GuiData::editMapPosition.contains(mousePosition)) {
        GuiData::current_maps = mapSerializer.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToEdit = true;
      }
      if (GuiData::createCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readCurrentDirectoryContents("campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToCreate = true;
      }
      if (GuiData::editCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = mapSerializer.readCurrentDirectoryContents("campaign");
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
          if (GuiData::isChoosingMapToEdit) {
            GuiData::isChoosingMapToEdit = false;
            GuiData::isEditingMap = true;
          }
          string ext = ".map";
          GuiData::chosenMap = string(GuiData::current_maps[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readMapJSON(GuiData::chosenMap);
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
        }
          string ext = ".campaign";
          GuiData::chosenCampaign = string(GuiData::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readCampaignJSON(GuiData::chosenCampaign);
      }
    }
  }
}

void Events::respondToRealTimeTypeFeedback(sf::Event& evt) {
    if (evt.type == sf::Event::TextEntered) {
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
              GuiData::createdMap = GuiData::createdMap + ".map";
              GuiData::isChoosingMapToCreate = false;
              GuiData::isCreatingMap = true;

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
              GuiData::createdCampaign = GuiData::createdCampaign + ".campaign";
              GuiData::isChoosingCampaignToCreate = false;
              GuiData::isCreatingCampaign = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
              GuiData::createdCampaign.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdCampaign += evt.text.unicode;
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
        GuiData::isCreatingMap = false;
        GuiData::isCreatingCampaign = false;
        GuiData::shouldShowNameConflictError = false;

        GuiData::createdMap = "";
        GuiData::chosenMap = "";
        GuiData::createdCampaign = "";
        GuiData::chosenCampaign = "";
      }
    }
  }
}

void Events::respondToSaveMapCampaign(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::saveButton.getGlobalBounds().contains(mousePosition)) {
      MapCampaignFileIO mfio;
      if (GuiData::isEditingMap) {
        mfio.saveMapJSON(GuiData::chosenMap);
      }
      if (GuiData::isCreatingMap) {
        mfio.saveMapJSON(GuiData::createdMap);
      }
      if (GuiData::isEditingCampaign) {
        mfio.saveCampaignJSON(GuiData::chosenCampaign);
      }
      if (GuiData::isCreatingCampaign) {
        mfio.saveCampaignJSON(GuiData::createdCampaign);
      }
    }
  }
}

void Events::respondToWidthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isEditingMap || GuiData::isCreatingMap) {
      if (GuiData::widthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapWidth += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}
void Events::respondToWidthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isEditingMap || GuiData::isCreatingMap) {
      if (GuiData::widthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::currentMapWidth > 0) {
          GuiData::currentMapWidth -= 1;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}
void Events::respondToLengthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isEditingMap || GuiData::isCreatingMap) {
      if (GuiData::lengthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapLength += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToLengthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isEditingMap || GuiData::isCreatingMap) {
      if (GuiData::lengthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::currentMapLength > 0) {
          GuiData::currentMapLength -= 1;
          GuiData::shouldBlockThread = true;
        }
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
