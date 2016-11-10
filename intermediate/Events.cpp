//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "GuiData.h"
#include "Events.h"
#include "MapCampaignFileIO.h"
#include "CharacterFileIO.h"
#include "Utils.h"

using std::stoi;
using std::cout;
using std::endl;

void Events::respondToSelectionBoxClick(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::SELECTION_BOXES_APPEAR_TIME && GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      Utils util;
      if (GuiData::createMapPosition.contains(mousePosition)) {
        GuiData::current_maps = util.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToCreate = true;
      }
      if (GuiData::editMapPosition.contains(mousePosition)) {
        GuiData::current_maps = util.readCurrentDirectoryContents("map");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingMapToEdit = true;
      }
      if (GuiData::createCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = util.readCurrentDirectoryContents("campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToCreate = true;
        GuiData::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (GuiData::editCampaignPosition.contains(mousePosition)) {
        GuiData::current_campaigns = util.readCurrentDirectoryContents("campaign");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToEdit = true;
        GuiData::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (GuiData::createCharacterPosition.contains(mousePosition)) {
        GuiData::current_characters = util.readCurrentDirectoryContents("character");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCharacterToCreate = true;
      }
      if (GuiData::editCharacterPosition.contains(mousePosition)) {
        GuiData::current_characters = util.readCurrentDirectoryContents("character");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCharacterToEdit = true;

      }
      if (GuiData::createItemPosition.contains(mousePosition)) {
        GuiData::current_items = util.readCurrentDirectoryContents("item");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingItemToCreate = true;

      }
      if (GuiData::editItemPosition.contains(mousePosition)) {
        GuiData::current_items = util.readCurrentDirectoryContents("item");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingItemToEdit= true;
      }
      if (GuiData::playPosition.contains(mousePosition)) {
        GuiData::current_campaigns = util.readCurrentDirectoryContents("campaign");
        GuiData::current_maps = util.readCurrentDirectoryContents("map");
        GuiData::current_characters = util.readCurrentDirectoryContents("character");
        GuiData::isSelectingChoice = false;
        GuiData::isChoosingCampaignToPlay = true;
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
          string ext = ".map";
          GuiData::chosenMap = string(GuiData::current_maps[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readMapJSON(GuiData::chosenMap);
          if (!GameData::currentMapObject->validatePath()) {
            delete GameData::currentMapObject;
            GameData::currentMapObject = NULL;
            GuiData::shouldShowMapValidationError = true;
          } else {
            GuiData::shouldShowMapValidationError = false;
            GuiData::isChoosingMapToEdit = false;
            GuiData::isEditingMap = true;
          }
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }

  if (GuiData::isChoosingCampaignToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_campaign_positions.size(); i++) {
        if (GuiData::current_campaign_positions[i].contains(mousePosition)) {
          string ext = ".campaign";
          GuiData::chosenCampaign = string(GuiData::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          Utils util;
          mfio.readCampaignJSON(GuiData::chosenCampaign);
          GuiData::current_maps = util.readCurrentDirectoryContents("map");
          if (!GameData::currentCampaignObject->isCampaignValid(GuiData::current_maps)) {
            GuiData::shouldShowCampaignValidationError = true;
          } else {
            GuiData::shouldShowCampaignValidationError = false;
            GuiData::isChoosingCampaignToEdit = false;
            GuiData::isEditingCampaign = true;
          }
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }

  if (GuiData::isChoosingCharacterToEdit) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_character_positions.size(); i++) {
        if (GuiData::current_character_positions[i].contains(mousePosition)) {

          string ext = ".character";
          GuiData::chosenCharacter = string(GuiData::current_characters[i]) + string(ext);
          CharacterFileIO cfio;
          GameData::currentCharacterObject = new Character();
          cfio.readCharacter(GuiData::chosenCharacter, *GameData::currentCharacterObject);
          GuiData::shouldShowCharacterValidationError = false;
          GuiData::isChoosingCharacterToEdit = false;
          GuiData::isEditingCharacter = true;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }

  if (GuiData::isChoosingCampaignToPlay) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_campaign_positions.size(); i++) {
        if (GuiData::current_campaign_positions[i].contains(mousePosition)) {
          string ext = ".campaign";
          GuiData::playedCampaign = string(GuiData::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          Utils util;
          mfio.readCampaignJSON(GuiData::playedCampaign);
          GuiData::current_maps = util.readCurrentDirectoryContents("map");
          if (!GameData::currentCampaignObject->isCampaignValid(GuiData::current_maps)) {
            GuiData::shouldShowCampaignValidationError = true;
          } else {
            GuiData::shouldShowCampaignValidationError = false;
            GuiData::isChoosingCampaignToPlay = false;
            GuiData::isChoosingCharacterToPlay = true;
          }
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }

  if (GuiData::isChoosingCharacterToPlay) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)GuiData::current_character_positions.size(); i++) {
        if (GuiData::current_character_positions[i].contains(mousePosition)) {
          string ext = ".character";
          GuiData::playedCampaign = string(GuiData::current_characters[i]) + string(ext);
          CharacterFileIO cfio;
          cfio.readCharacter(GuiData::playedCampaign, *GameData::currentCharacterObject);
          GuiData::isChoosingCharacterToPlay = false;
          GuiData::isPlayingGame = true;
          GameData::currentCharacterObject->displayCharacter();
          GuiData::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[GuiData::GamePlayCurrentMap];
          MapCampaignFileIO mfio;
          mfio.readMapJSON(GuiData::playedMap+".map");
          GameData::currentMapObject->setCurrentPosition();
          GuiData::shouldBlockThread = true;
        }
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
              GuiData::isSelectingMapSize = true;
              GuiData::shouldBlockThread = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::createdMap.length() != 0)
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
              delete GameData::currentCampaignObject;
              GameData::currentCampaignObject = new Campaign();
              GuiData::shouldBlockThread = true;

            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::createdCampaign.length() != 0)
              GuiData::createdCampaign.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdCampaign += evt.text.unicode;
          }
        }


        if (GuiData::isChoosingCharacterToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_characters.size(); i++) {
              if (GuiData::current_characters[i] == GuiData::createdCharacter) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::createdCharacter = GuiData::createdCharacter + ".character";
              GuiData::isChoosingCharacterToCreate = false;
              GuiData::isCreatingCharacter = true;
              GuiData::shouldBlockThread = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::createdCharacter.length() != 0)
              GuiData::createdCharacter.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdCharacter += evt.text.unicode;
          }
        }


        if (GuiData::isChoosingItemToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)GuiData::current_items.size(); i++) {
              if (GuiData::current_items[i] == GuiData::createdItem) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              GuiData::shouldShowNameConflictError = true;
            } else {
              GuiData::createdItem = GuiData::createdItem + ".item";
              GuiData::isChoosingItemToCreate = false;
              GuiData::isCreatingItem = true;
              GuiData::shouldBlockThread = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::createdItem.length() != 0)
              GuiData::createdItem.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdItem += evt.text.unicode;
          }
        }

        if (GuiData::isCreatingCharacter) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::createdCharacterArgs.length() != 0)
              GuiData::createdCharacterArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::createdCharacterArgs += evt.text.unicode;
          }
        }

        if (GuiData::isEditingCharacter) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (GuiData::chosenCharacterArgs.length() != 0)
              GuiData::chosenCharacterArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              GuiData::chosenCharacterArgs += evt.text.unicode;
          }
        }


    }
}

void Events::respondToHomeButtonClick(sf::RenderWindow& window) {
  if (!GuiData::isSelectingChoice) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::HomeButton.getGlobalBounds().contains(mousePosition)) {
        GuiData::isSelectingChoice = true;
        GuiData::hasCreateMapPosition = false;
        GuiData::hasReachedEndOfMap = false;
        GuiData::hasEditMapPosition = false;
        GuiData::hasCreateCampaignPosition = false;
        GuiData::hasEditCampaignPosition = false;
        GuiData::hasCreateCharacterPosition = false;
        GuiData::hasEditCharacterPosition = false;
        GuiData::isPlayingGame = false;
        GuiData::hasCreateItemPosition = false;
        GuiData::hasEditItemPosition = false;
        GuiData::hasPlayPosition= false;
        GuiData::isSelectingMapSize = false;
        GuiData::isChoosingMapToCreate = false;
        GuiData::isChoosingMapToEdit = false;
        GuiData::isChoosingCampaignToCreate = false;
        GuiData::isChoosingCampaignToEdit = false;
        GuiData::isEditingCampaign = false;
        GuiData::isEditingMap = false;
        GuiData::isCreatingCampaign = false;
        GuiData::isCreatingMap = false;
        GuiData::shouldShowNameConflictError = false;
        GuiData::isMapValid = false;
        GuiData::isChoosingCharacterToCreate = false;
        GuiData::isChoosingCharacterToEdit = false;
        GuiData::isChoosingItemToCreate = false;
        GuiData::isChoosingItemToEdit = false;
        GuiData::isChoosingCampaignToPlay = false;
        GuiData::isChoosingCharacterToPlay = false;
        GuiData::isCreatingCharacter = false;
        GuiData::isCreatingItem = false;
        GuiData::isEditingCharacter = false;
        GuiData::isEditingItem = false;
        GuiData::shouldBlockThread = false;
        GuiData::shouldShowCampaignValidationError = false;
        GuiData::shouldShowMapValidationError = false;
        GuiData::shouldShowCharacterValidationError = false;
        GuiData::shouldShowItemValidationError = false;

        GuiData::createdMap = "";
        GuiData::chosenMap = "";
        GuiData::createdCampaign = "";
        GuiData::chosenCampaign = "";
        GuiData::createdCharacter = "";
        GuiData::chosenCharacter= "";
        GuiData::createdItem= "";
        GuiData::chosenItem= "";
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
        if (GameData::currentMapObject->validatePath()) {
          GuiData::shouldShowMapValidationError = false;
          mfio.saveMapJSON(GuiData::chosenMap);
        } else {
          GuiData::shouldShowMapValidationError = true;
        }
      }
      if (GuiData::isCreatingMap) {
        if (GameData::currentMapObject->validatePath()) {
          GuiData::shouldShowMapValidationError = false;
          mfio.saveMapJSON(GuiData::createdMap);
        } else {
          GuiData::shouldShowMapValidationError = true;
        }
      }
      if (GuiData::isEditingCampaign) {
        if (GameData::currentCampaignObject->isCampaignValid(GuiData::current_maps)) {
          GuiData::shouldShowCampaignValidationError = false;
          mfio.saveCampaignJSON(GuiData::chosenCampaign);
        } else {
          GuiData::shouldShowCampaignValidationError = true;
        }
      }
      if (GuiData::isCreatingCampaign) {
        if (GameData::currentCampaignObject->isCampaignValid(GuiData::current_maps)) {
          GuiData::shouldShowCampaignValidationError = false;
          mfio.saveCampaignJSON(GuiData::createdCampaign);
        } else {
          GuiData::shouldShowCampaignValidationError = true;
        }
      }

      if (GuiData::isCreatingCharacter || GuiData::isEditingCharacter) {
        string args;
        string tempCreatedArgs(GuiData::createdCharacterArgs);
        string tempChosenArgs(GuiData::chosenCharacterArgs);
        string fileNameOutput;
        if (GuiData::isCreatingCharacter) {
          args = string(tempCreatedArgs);
          fileNameOutput = GuiData::createdCharacter;
        }
        if (GuiData::isEditingCharacter) {
          args = string(tempChosenArgs);
          fileNameOutput = GuiData::chosenCharacter;
        }

        // check if csv is valid
        Utils util;
        util.removeSpaceCharFromString(args);
        vector<string> stringArgElements;
        vector<int> intArgElements;
        util.split(args, ',', stringArgElements);

        if (stringArgElements.size() != 6) {
          cout << "INVALID: Must provide 6 ability values." << endl;
          GuiData::shouldShowCharacterValidationError = true;
          return;
        }

        for (int i = 0; i < (int)stringArgElements.size(); i++) {
          try {
            intArgElements.push_back(stoi(stringArgElements[i]));
          } catch (...) {
            //string to int cast failed
            cout << "INVALID: Ability values must be integers." << endl;
            GuiData::shouldShowCharacterValidationError = true;
            return;
          }
        }

        // check if character is valid
        GameData::currentCharacterObject = new Character(
          intArgElements[0],
          intArgElements[1],
          intArgElements[2],
          intArgElements[3],
          intArgElements[4],
          intArgElements[5]
        );

        // Character is valid
        GuiData::shouldShowCharacterValidationError = false;
        CharacterFileIO cfio;
        cfio.saveCharacter(fileNameOutput, *GameData::currentCharacterObject);
        GameData::currentCharacterObject->displayCharacter();
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToWidthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::widthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::tempMapWidth += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}
void Events::respondToWidthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::widthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::tempMapWidth > 4) {
            GuiData::tempMapWidth -= 1;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}
void Events::respondToLengthPlusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::lengthPlus.getGlobalBounds().contains(mousePosition)) {
        GuiData::tempMapLength += 1;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToLengthMinusClick(sf::RenderWindow& window) {
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (GuiData::isSelectingMapSize) {
      if (GuiData::lengthMinus.getGlobalBounds().contains(mousePosition)) {
        if (GuiData::tempMapLength > 4) {
          GuiData::tempMapLength -= 1;
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}


void Events::respondToMapCreateOkButton(sf::RenderWindow& window) {
  if (GuiData::isSelectingMapSize) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::mapCreateOkButton.getGlobalBounds().contains(mousePosition)) {
        delete GameData::currentMapObject;
        int numBoxes = GuiData::tempMapWidth * GuiData::tempMapLength;
        string placement(numBoxes, ' ');

        // No saving here, because the map won't be valid to begin with.
        GameData::currentMapObject = new Map(GuiData::tempMapWidth, GuiData::tempMapLength, placement);

        GuiData::isSelectingMapSize = false;
        GuiData::isCreatingMap = true;
        GuiData::shouldBlockThread = true;
      }
    }
  }
}

void Events::respondToMapTileSelect(sf::RenderWindow& window) {
  if (GuiData::isEditingMap || GuiData::isCreatingMap) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (GuiData::wallSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'W';
      }
      if (GuiData::exitSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'E';
      }
      if (GuiData::startSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'S';
      }
      if (GuiData::treasureSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'T';
      }
      if (GuiData::monsterSelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = 'O';
      }
      if (GuiData::emptySelectionSprite.getGlobalBounds().contains(mousePosition)) {
        GuiData::currentMapTileSelectedChar = ' ';
      }
    }
  }
}

void Events::respondToMapBoxClick(sf::RenderWindow& window) {
  if (GuiData::isEditingMap || GuiData::isCreatingMap) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      int tempWidth = GameData::currentMapObject->getMapWidth();
      int tempLength = GameData::currentMapObject->getMapLength();

      for (int i = 0; i< tempWidth; i++) {
        for (int j =0; j < tempLength; j++) {
          if (GuiData::currentMapTilePositions[i][j].contains(mousePosition)) {
            GameData::currentMapObject->setCell(i, j, GuiData::currentMapTileSelectedChar);
            GuiData::shouldBlockThread = true;
          }
        }
      }
    }
  }
}

void Events::respondToCampaignAvailableMapsClick(sf::RenderWindow& window) {
  if (GuiData::isEditingCampaign|| GuiData::isCreatingCampaign) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      for (int i = 0; i < (int)GuiData::current_available_map_positions.size(); i++) {
        if (GuiData::current_available_map_positions[i].contains(mousePosition)) {
          vector<string> tempMapOrder = GameData::currentCampaignObject->getCampaignMapOrder();
          tempMapOrder.push_back(GuiData::current_maps[i]);
          GameData::currentCampaignObject->setCampaignMapOrder(tempMapOrder);
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}

void Events::respondToCampaignMapOrderClick(sf::RenderWindow& window) {
  if (GuiData::isEditingCampaign|| GuiData::isCreatingCampaign) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      for (int i = 0; i < (int)GuiData::current_campaign_map_order_positions.size(); i++) {
        if (GuiData::current_campaign_map_order_positions[i].contains(mousePosition)) {
          vector<string> tempMapOrder = GameData::currentCampaignObject->getCampaignMapOrder();
          tempMapOrder.erase(tempMapOrder.begin()+i);
          GameData::currentCampaignObject->setCampaignMapOrder(tempMapOrder);
          GuiData::shouldBlockThread = true;
        }
      }
    }
  }
}

void Events::respondToPlayingGameEvents(sf::RenderWindow& window) {
  if (GuiData::isPlayingGame) {

    if (GuiData::hasReachedEndOfMap) {
      GuiData::hasReachedEndOfMap = false;
      GuiData::GamePlayCurrentMap++;
      if (GuiData::GamePlayCurrentMap != (int)GameData::currentCampaignObject->getCampaignMapOrder().size()) {
        GameData::currentCharacterObject->levelUp();
        GameData::currentCharacterObject->displayCharacter();
        GuiData::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[GuiData::GamePlayCurrentMap];
        MapCampaignFileIO mfio;
        mfio.readMapJSON(GuiData::playedMap+".map");
        GameData::currentMapObject->setCurrentPosition();
      }
      else {
        cout << "!!! YOU WON THE CAMPAIGN !!!" << endl;
        exit(0);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
      GameData::currentMapObject->openChest();
      GuiData::shouldBlockThread = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
      GameData::currentCharacterObject->displayCharacter();
      GuiData::shouldBlockThread = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      GameData::currentMapObject->moveLeft();
      GuiData::shouldBlockThread = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      GameData::currentMapObject->moveRight();
      GuiData::shouldBlockThread = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      GameData::currentMapObject->moveUp();
      GuiData::shouldBlockThread = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      GameData::currentMapObject->moveDown();
      GuiData::shouldBlockThread = true;
    }
  }
}


