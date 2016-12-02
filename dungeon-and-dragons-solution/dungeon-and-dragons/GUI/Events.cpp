//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include "../ConsoleActions.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <tuple>
#include <SFML/Graphics.hpp>
#include "../GameData.h"
#include "Gui.h"
#include "Events.h"
#include "../Map/MapCampaignFileIO.h"
#include "../Character/CharacterFileIO.h"
#include "../Character/CharacterBuilder.h"
#include "../Character/CharacterGenerator.h"
#include "../Character/HumanPlayerStrategy.h"
#include "Utils.h"

using std::stoi;
using std::cout;
using std::endl;

std::random_device rd;     // only used once to initialise (seed) engine
std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)

void Events::respondToSelectionBoxClick(sf::RenderWindow& window, sf::Event& evt) {
  if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    Utils util;
    if (Gui::isSelectingChoice) {
      if (Gui::createMapPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Map Creation.");
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::isSelectingChoice = false;
        Gui::isChoosingMapToCreate = true;
      }
      if (Gui::editMapPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Map Editing.");
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::isSelectingChoice = false;
        Gui::isChoosingMapToEdit = true;
      }
      if (Gui::createCampaignPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Campaign Creation.");
        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToCreate = true;
        Gui::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (Gui::editCampaignPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Campaign Editing.");
        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToEdit = true;
        Gui::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (Gui::createCharacterPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Character Creation.");
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::current_items = util.readCurrentDirectoryContents("items");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCharacterToCreate = true;
      }
      if (Gui::editCharacterPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Character Editing.");
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::current_items = util.readCurrentDirectoryContents("items");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCharacterToEdit = true;
      }
      if (Gui::createItemPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Item Creation.");
        Gui::current_items = util.readCurrentDirectoryContents("item");
        Gui::isSelectingChoice = false;
        Gui::isChoosingItemToCreate = true;

      }
      if (Gui::editItemPosition.contains(mousePosition)) {
		UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected Item Editing.");
        Gui::current_items = util.readCurrentDirectoryContents("item");
        Gui::isSelectingChoice = false;
        Gui::isChoosingItemToEdit= true;
      }
      if (Gui::playPosition.contains(mousePosition)) {
		  UpdateLog("Events", "respondToSelectionBoxClick", "Player has selected PLAY GAME.");
        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToPlay = true;
      }
      if (Gui::consoleButtonPosition.contains(mousePosition)) {
		  UpdateLog("Events", "respondToSelectionBoxClick", "Play activated Console");



		  ConsoleActions::TogglingLogger();



        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToPlay = true;
      }
    }
  }
}

void Events::respondToFileSelectionClick(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isChoosingMapToEdit) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_map_positions.size(); i++) {
        if (Gui::current_map_positions[i].contains(mousePosition)) {
          string ext = ".map";
          Gui::chosenMap = string(Gui::current_maps[i]) + string(ext);
          MapCampaignFileIO mfio;
          mfio.readMapJSON(Gui::chosenMap);
          if (!GameData::currentMapObject->validatePath()) {
            delete GameData::currentMapObject;
            GameData::currentMapObject = NULL;
            Gui::shouldShowMapValidationError = true;
          } else {
            Gui::shouldShowMapValidationError = false;
            Gui::isChoosingMapToEdit = false;
            Gui::isEditingMap = true;
          }
        }
      }
    }
  }

  if (Gui::isCreatingCharacter || Gui::isEditingCharacter) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_item_positions.size(); i++) {
        if (Gui::current_item_positions[i].contains(mousePosition)) {
          string ext = ".item";
          Gui::chosenItem = string(Gui::current_items[i]) + string(ext);
          ItemFileIO ifio;
          cout << "before" << endl;
          Gui::tempItems.push_back(ifio.readItem(Gui::chosenItem));
          GameData::currentCharacterObject->equipItem(*ifio.readItem(Gui::chosenItem));
          cout << "after" << endl;
        }
      }
    }
  }
  if (Gui::isChoosingCampaignToEdit) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_campaign_positions.size(); i++) {
        if (Gui::current_campaign_positions[i].contains(mousePosition)) {
          string ext = ".campaign";
          Gui::chosenCampaign = string(Gui::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          Utils util;
          mfio.readCampaignJSON(Gui::chosenCampaign);
          Gui::current_maps = util.readCurrentDirectoryContents("map");
          if (!GameData::currentCampaignObject->isCampaignValid(Gui::current_maps)) {
            Gui::shouldShowCampaignValidationError = true;
          } else {
            Gui::shouldShowCampaignValidationError = false;
            Gui::isChoosingCampaignToEdit = false;
            Gui::isEditingCampaign = true;
          }
        }
      }
    }
  }

  if (Gui::isChoosingCharacterToEdit) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_character_positions.size(); i++) {
        if (Gui::current_character_positions[i].contains(mousePosition)) {

          string ext = ".character";
          Gui::chosenCharacter = string(Gui::current_characters[i]) + string(ext);
          CharacterFileIO cfio;
          GameData::currentCharacterObject = cfio.readCharacter(Gui::chosenCharacter);
          Gui::shouldShowCharacterValidationError = false;
          Gui::isChoosingCharacterToEdit = false;
          Gui::isEditingCharacter = true;
          Utils util;
        Gui::current_items = util.readCurrentDirectoryContents("item");
        }
      }
    }
  }
  if (Gui::isChoosingItemToEdit) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_item_positions.size(); i++) {
        if (Gui::current_item_positions[i].contains(mousePosition)) {
          string ext = ".item";
          Gui::chosenItem = string(Gui::current_items[i]) + string(ext);
          ItemFileIO cfio;
          GameData::currentItemObject = cfio.readItem(Gui::chosenItem);
          Gui::shouldShowItemValidationError = false;
          Gui::isChoosingItemToEdit = false;
          Gui::isEditingItem = true;
        }
      }
    }
  }

  if (Gui::isChoosingCampaignToPlay) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_campaign_positions.size(); i++) {
        if (Gui::current_campaign_positions[i].contains(mousePosition)) {
          string ext = ".campaign";
          Gui::playedCampaign = string(Gui::current_campaigns[i]) + string(ext);
          MapCampaignFileIO mfio;
          Utils util;
          mfio.readCampaignJSON(Gui::playedCampaign);
          Gui::current_maps = util.readCurrentDirectoryContents("map");
          if (!GameData::currentCampaignObject->isCampaignValid(Gui::current_maps)) {
            Gui::shouldShowCampaignValidationError = true;
          } else {
            Gui::shouldShowCampaignValidationError = false;
            Gui::isChoosingCampaignToPlay = false;
            Gui::isChoosingCharacterToPlay = true;
          }
        }
      }
    }
  }

  if (Gui::isChoosingCharacterToPlay) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

      for (int i = 0; i < (int)Gui::current_character_positions.size(); i++) {
        if (Gui::current_character_positions[i].contains(mousePosition)) {
          string ext = ".character";
          Gui::playedCampaign = string(Gui::current_characters[i]) + string(ext);
          CharacterFileIO cfio;
          GameData::currentCharacterObject = cfio.readCharacter(Gui::playedCampaign);
          if (GameData::currentCharacterObject->getTypeOnMap() != 'S') {
            Gui::shouldShowPlayerTypeError = true;
            return;
          }
          GameData::currentCharacterObject->setTypeOnMap('S');
          GameData::gameCharacters.push_back(GameData::currentCharacterObject);

          // Setup for remainder of game.

          Gui::shouldShowPlayerTypeError = false;
          Gui::isChoosingCharacterToPlay = false;
          Gui::isPlayingGame = true;
          Gui::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[Gui::GamePlayCurrentMap];
          MapCampaignFileIO mfio;
          mfio.readMapJSON(Gui::playedMap+".map");


          this->loadCharactersOnNewMap();

        }
      }
    }
  }
}

void Events::respondToRealTimeTypeFeedback(sf::Event& evt) {
    if (evt.type == sf::Event::TextEntered) {


        if (Gui::isChoosingMapToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)Gui::current_maps.size(); i++) {
              if (Gui::current_maps[i] == Gui::createdMap) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              Gui::shouldShowNameConflictError = true;
            } else {
              Gui::createdMap = Gui::createdMap + ".map";
              Gui::isChoosingMapToCreate = false;
              Gui::isSelectingMapSize = true;
  
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdMap.length() != 0)
              Gui::createdMap.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdMap += evt.text.unicode;
          }
        }


        if (Gui::isChoosingCampaignToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)Gui::current_campaigns.size(); i++) {
              if (Gui::current_campaigns[i] == Gui::createdCampaign) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              Gui::shouldShowNameConflictError = true;
            } else {
              Gui::createdCampaign = Gui::createdCampaign + ".campaign";
              Gui::isChoosingCampaignToCreate = false;
              Gui::isCreatingCampaign = true;
              delete GameData::currentCampaignObject;
              GameData::currentCampaignObject = new MapCampaign();
  

            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdCampaign.length() != 0)
              Gui::createdCampaign.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdCampaign += evt.text.unicode;
          }
        }


        if (Gui::isChoosingCharacterToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)Gui::current_characters.size(); i++) {
              if (Gui::current_characters[i] == Gui::createdCharacter) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              Gui::shouldShowNameConflictError = true;
            } else {
              Gui::createdCharacter = Gui::createdCharacter + ".character";
              Gui::isChoosingCharacterToCreate = false;
              Gui::isCreatingCharacter = true;
          Utils util;
        Gui::current_items = util.readCurrentDirectoryContents("item");
  
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdCharacter.length() != 0)
              Gui::createdCharacter.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdCharacter += evt.text.unicode;
          }
        }


        if (Gui::isChoosingItemToCreate) {
          if (evt.text.unicode == 13) { // ENTER
            bool hasNameConflict = false;
            for (int i = 0; i < (int)Gui::current_items.size(); i++) {
              if (Gui::current_items[i] == Gui::createdItem) {
                hasNameConflict = true;
                break;
              }
            }
            if (hasNameConflict) {
              Gui::shouldShowNameConflictError = true;
            } else {
              Gui::createdItem = Gui::createdItem + ".item";
              Gui::isChoosingItemToCreate = false;
              Gui::isCreatingItem = true;
            }
          } else if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdItem.length() != 0)
              Gui::createdItem.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdItem += evt.text.unicode;
          }
        }

        if (Gui::isCreatingCharacter) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdCharacterArgs.length() != 0)
              Gui::createdCharacterArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdCharacterArgs += evt.text.unicode;
          }
        }

        if (Gui::isEditingCharacter) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::chosenCharacterArgs.length() != 0)
              Gui::chosenCharacterArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::chosenCharacterArgs += evt.text.unicode;
          }
        }

        if (Gui::isCreatingItem) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::createdItemArgs.length() != 0)
              Gui::createdItemArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::createdItemArgs += evt.text.unicode;
          }
        }

        if (Gui::isEditingItem) {
          if (evt.text.unicode == 8) { // BACKSPACE
            if (Gui::chosenItemArgs.length() != 0)
              Gui::chosenItemArgs.pop_back();
          } else if (evt.text.unicode < 128) { // ASCII char
              Gui::chosenItemArgs += evt.text.unicode;
          }
        }
    }
}

void Events::respondToHomeButtonClick(sf::RenderWindow& window, sf::Event& evt) {
  if (!Gui::isSelectingChoice) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (Gui::homeButtonPosition.contains(mousePosition)) {
        Gui::isSelectingChoice = true;
        Gui::isPlayingGame = false;
        Gui::isSelectingMapSize = false;
        Gui::isChoosingMapToCreate = false;
        Gui::isChoosingMapToEdit = false;
        Gui::isChoosingCampaignToCreate = false;
        Gui::isChoosingCampaignToEdit = false;
        Gui::isEditingCampaign = false;
        Gui::isEditingMap = false;
        Gui::isCreatingCampaign = false;
        Gui::isCreatingMap = false;
        Gui::shouldShowNameConflictError = false;
        Gui::isMapValid = false;
        Gui::isChoosingCharacterToCreate = false;
        Gui::isChoosingCharacterToEdit = false;
        Gui::isChoosingItemToCreate = false;
        Gui::isChoosingItemToEdit = false;
        Gui::isChoosingCampaignToPlay = false;
        Gui::isChoosingCharacterToPlay = false;
        Gui::isCreatingCharacter = false;
        Gui::isCreatingItem = false;
        Gui::isEditingCharacter = false;
        Gui::isEditingItem = false;
        Gui::shouldShowCampaignValidationError = false;
        Gui::shouldShowMapValidationError = false;
        Gui::shouldShowCharacterValidationError = false;
        Gui::shouldShowItemValidationError = false;

        Gui::createdMap = "";
        Gui::chosenMap = "";
        Gui::createdCampaign = "";
        Gui::chosenCampaign = "";
        Gui::createdCharacter = "";
        Gui::chosenCharacter= "";
        Gui::createdItem= "";
        Gui::chosenItem= "";
      }
    }
  }
}

void Events::respondToSaveMapCampaign(sf::RenderWindow& window, sf::Event& evt) {
  if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    if (Gui::saveButtonPosition.contains(mousePosition)) {
      MapCampaignFileIO mfio;
      if (Gui::isEditingMap) {
        if (GameData::currentMapObject->validatePath()) {
          Gui::shouldShowMapValidationError = false;
          mfio.saveMapJSON(Gui::chosenMap);
        } else {
          Gui::shouldShowMapValidationError = true;
        }
      }
      if (Gui::isCreatingMap) {
        if (GameData::currentMapObject->validatePath()) {
          Gui::shouldShowMapValidationError = false;
          mfio.saveMapJSON(Gui::createdMap);
        } else {
          Gui::shouldShowMapValidationError = true;
        }
      }
      if (Gui::isEditingCampaign) {
        if (GameData::currentCampaignObject->isCampaignValid(Gui::current_maps)) {
          Gui::shouldShowCampaignValidationError = false;
          mfio.saveCampaignJSON(Gui::chosenCampaign);
        } else {
          Gui::shouldShowCampaignValidationError = true;
        }
      }
      if (Gui::isCreatingCampaign) {
        if (GameData::currentCampaignObject->isCampaignValid(Gui::current_maps)) {
          Gui::shouldShowCampaignValidationError = false;
          mfio.saveCampaignJSON(Gui::createdCampaign);
        } else {
          Gui::shouldShowCampaignValidationError = true;
        }
      }

      if (Gui::isCreatingItem || Gui::isEditingItem) {

        string args;
        string fileNameOutput;
        if (Gui::isCreatingItem) {
          string tempCreatedArgs(Gui::createdItemArgs);
          args = string(tempCreatedArgs);
          fileNameOutput = Gui::createdItem;
        }
        if (Gui::isEditingItem) {
        string tempChosenArgs(Gui::chosenItemArgs);
          args = string(tempChosenArgs);
          fileNameOutput = Gui::chosenItem;
        }

        // check if csv is valid
        Utils util;

        vector<string> stringArgElements = util.splitBySpace(args);

        cout << stringArgElements.size()  << endl;
        if (stringArgElements.size() != 4) {
          cout << "INVALID: Must provide 4 values to build item." << endl;
          Gui::shouldShowItemValidationError = true;
          return;
        }

        GameData::currentEnhancementObject = new Enhancement(stringArgElements[2], stoi(stringArgElements[3]));
	if (!GameData::currentEnhancementObject->validateBonus()) {
          cout << "ERROR: Enhancement bonus invalid";
          Gui::shouldShowItemValidationError = true;
          return;
	}
	else {
          GameData::currentItemObject = new Item(stringArgElements[1], *GameData::currentEnhancementObject, stringArgElements[0]);
          if (!GameData::currentItemObject->validateItemType(stringArgElements[1]) || !GameData::currentItemObject->validateByType(stringArgElements[1])) {
            cout << "ERROR: Enhancement bonus invalid";
            Gui::shouldShowItemValidationError = true;
            return;
          }
          Gui::shouldShowItemValidationError = false;
          ItemFileIO mfio;
          mfio.saveItem(stringArgElements[0]+".item", *GameData::currentItemObject);
	}
      }

      if (Gui::isCreatingCharacter || Gui::isEditingCharacter) {

        string args;
        string fileNameOutput;
        if (Gui::isCreatingCharacter) {
          string tempCreatedArgs(Gui::createdCharacterArgs);
          args = string(tempCreatedArgs);
          fileNameOutput = Gui::createdCharacter;
        }
        if (Gui::isEditingCharacter) {
        string tempChosenArgs(Gui::chosenCharacterArgs);
          args = string(tempChosenArgs);
          fileNameOutput = Gui::chosenCharacter;
        }

        // check if csv is valid
        Utils util;

        vector<string> stringArgElements = util.splitBySpace(args);

        if (stringArgElements.size() != 3) {
          cout << "INVALID: Must provide 3 values to build character." << endl;
          Gui::shouldShowCharacterValidationError = true;
          return;
        }
        if (stringArgElements[0] != "Tank" &&
            stringArgElements[0] != "Nimble" &
            stringArgElements[0] != "Bully" ) {
          //cout << "INVALID: Fighter must be Tank, Nimble or Bully." << endl;
          cout << stringArgElements[0] << endl;
          cout << "\""<< stringArgElements[0]<<"\""<< endl;
          Gui::shouldShowCharacterValidationError = true;
          return;
        }

        if (stringArgElements[1] != "Player" &&
            stringArgElements[1] != "Aggressor" &&
            stringArgElements[1] != "Friendly" ) {
          cout << "INVALID: Fighter must be Player, Friendly, or Aggressor." << endl;
          Gui::shouldShowCharacterValidationError = true;
          return;
        }

        int parsedLvl;
        try {
          parsedLvl = stoi(stringArgElements[2]);
        } catch (const std::invalid_argument& e) {
          cout << "INVALID: Fighter level must be an integer." << endl;
          Gui::shouldShowCharacterValidationError = true;
          return;
        }


        CharacterGenerator selectHero;
        CharacterBuilder* builder;
        if (stringArgElements[1] == "Player") {
          builder = new PlayerCharacterBuilder(stringArgElements[0], parsedLvl);
        }
        if (stringArgElements[1] == "Friendly") {
          builder = new FriendlyCharacterBuilder(stringArgElements[0], parsedLvl);
        }
        if (stringArgElements[1] == "Aggressor") {
          builder = new AggressorCharacterBuilder(stringArgElements[0], parsedLvl);
        }
        selectHero.setCharacterBuilder(builder);
        selectHero.createCharacter();
        GameData::currentCharacterObject = selectHero.getCharacter();

        if (!GameData::currentCharacterObject->validateNewCharacter()) {
          cout << "INVALID: Character ability scores are either below 3 or above 18." << endl;
          Gui::shouldShowCharacterValidationError = true;
          return;
        }

        //// Character is valid
        Gui::shouldShowCharacterValidationError = false;
        CharacterFileIO cfio;
        cfio.saveCharacter(fileNameOutput, GameData::currentCharacterObject);
      }
    }
  }
}

void Events::respondToMapSizeClick(sf::RenderWindow& window, sf::Event& evt) {
  if (evt.type == sf::Event::MouseButtonReleased &&
      evt.mouseButton.button == sf::Mouse::Left &&
      Gui::isSelectingMapSize) {

    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));

    if (Gui::widthPlusPosition.contains(mousePosition)) {
      Gui::tempMapWidth += 1;
    }
    if (Gui::lengthPlusPosition.contains(mousePosition)) {
      Gui::tempMapLength += 1;
    }
    if (Gui::widthMinusPosition.contains(mousePosition)) {
      if (Gui::tempMapWidth > 4) {
          Gui::tempMapWidth -= 1;
      }
    }
    if (Gui::lengthMinusPosition.contains(mousePosition)) {
      if (Gui::tempMapLength > 4) {
        Gui::tempMapLength -= 1;
      }
    }
  }
}

void Events::respondToMapCreateOkButton(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isSelectingMapSize) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (Gui::mapCreateOkPosition.contains(mousePosition)) {
        delete GameData::currentMapObject;
        int numBoxes = Gui::tempMapWidth * Gui::tempMapLength;
        string placement(numBoxes, ' ');

        // No saving here, because the map won't be valid to begin with.
        GameData::currentMapObject = new Map(Gui::tempMapWidth, Gui::tempMapLength, placement);

        Gui::isSelectingMapSize = false;
        Gui::isCreatingMap = true;
      }
    }
  }
}

void Events::respondToMapTileSelect(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isEditingMap || Gui::isCreatingMap) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      if (Gui::wallSelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'W';
      }
      if (Gui::exitSelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'E';
      }
      if (Gui::startSelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'S';
      }
      if (Gui::treasureSelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'T';
      }
      if (Gui::monsterSelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'O';
      }
      if (Gui::friendlySelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = 'C';
      }
      if (Gui::emptySelectionSpritePosition.contains(mousePosition)) {
        Gui::currentMapTileSelectedChar = ' ';
      }
    }
  }
}

void Events::respondToMapBoxClick(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isEditingMap || Gui::isCreatingMap) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));


      int tempWidth = GameData::currentMapObject->getMapWidth();
      int tempLength = GameData::currentMapObject->getMapLength();

      for (int i = 0; i< tempWidth; i++) {
        for (int j =0; j < tempLength; j++) {
          if (Gui::currentMapTilePositions[i][j].contains(mousePosition)) {

            // Need to check if a character or an item. If yes, need to select which one.
            // First, load all available characters
            if (Gui::currentMapTileSelectedChar == 'S' ||
                Gui::currentMapTileSelectedChar == 'C' ||
                Gui::currentMapTileSelectedChar == 'O') {
              Utils util;
              CharacterFileIO cfio;
              vector<string> availableCharactersFilenames = util.readCurrentDirectoryContents("character");

              for (size_t k = 0; k < (int)availableCharactersFilenames.size(); k++) {
                GameData::availableCharacters.push_back(
                    cfio.readCharacter(availableCharactersFilenames[k]+".character")
                );
              }

              GameData::availablePlayers.clear();
              GameData::availableFriendlies.clear();
              GameData::availableAggressors.clear();

              cout << GameData::availableFriendlies.size() << endl;

               //Sort available characters by player type
              for (int m = 0; m < (int)GameData::availableCharacters.size(); m++) {
                if (GameData::availableCharacters[m]->getTypeOnMap() == 'S') {
                  GameData::availablePlayers.push_back(GameData::availableCharacters[m]);
                }
                if (GameData::availableCharacters[m]->getTypeOnMap() == 'C') {
                  GameData::availableFriendlies.push_back(GameData::availableCharacters[m]);
                }
                if (GameData::availableCharacters[m]->getTypeOnMap() == 'O') {
                  GameData::availableAggressors.push_back(GameData::availableCharacters[m]);
                }
              }
              //// Check which type of character the user selected
              //// Randomly place an existing one of same type in that location
              if (Gui::currentMapTileSelectedChar == 'S') {
				  std::uniform_int_distribution<int> uni(0, (int)GameData::availablePlayers.size() - 1); // guaranteed unbiased
				  int random_int = uni(rng);
				  vector<int> currentPosition = { i,j };
				  GameData::availablePlayers[random_int]->setCurrentPosition(currentPosition);
				  GameData::gameCharacters.push_back(GameData::availablePlayers[random_int]);
              }
              if (Gui::currentMapTileSelectedChar == 'C') {
				  std::uniform_int_distribution<int> uni(0, (int)GameData::availableFriendlies.size() - 1); // guaranteed unbiased
				  int random_int = uni(rng);
				  vector<int> currentPosition = { i,j };
				  cout << random_int << endl;
				  GameData::availableFriendlies[random_int]->setCurrentPosition(currentPosition);
				  GameData::gameCharacters.push_back(GameData::availableFriendlies[random_int]);
              }
              if (Gui::currentMapTileSelectedChar == 'O') {
				  std::uniform_int_distribution<int> uni(0, (int)GameData::availableAggressors.size() - 1); // guaranteed unbiased
				  int random_int = uni(rng);
				  vector<int> currentPosition = { i,j };
				  GameData::availableAggressors[random_int]->setCurrentPosition(currentPosition);
				  GameData::gameCharacters.push_back(GameData::availableAggressors[random_int]);
              }
            }
            GameData::currentMapObject->setCell(i, j, Gui::currentMapTileSelectedChar);
          }
        }
      }
    }
  }
}

void Events::respondToCampaignAvailableMapsClick(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isEditingCampaign|| Gui::isCreatingCampaign) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      for (int i = 0; i < (int)Gui::current_available_map_positions.size(); i++) {
        if (Gui::current_available_map_positions[i].contains(mousePosition)) {
          vector<string> tempMapOrder = GameData::currentCampaignObject->getCampaignMapOrder();
          tempMapOrder.push_back(Gui::current_maps[i]);
          GameData::currentCampaignObject->setCampaignMapOrder(tempMapOrder);
        }
      }
    }
  }
}

void Events::respondToCampaignMapOrderClick(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isEditingCampaign|| Gui::isCreatingCampaign) {
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      for (int i = 0; i < (int)Gui::current_campaign_map_order_positions.size(); i++) {
        if (Gui::current_campaign_map_order_positions[i].contains(mousePosition)) {
          vector<string> tempMapOrder = GameData::currentCampaignObject->getCampaignMapOrder();
          tempMapOrder.erase(tempMapOrder.begin()+i);
          GameData::currentCampaignObject->setCampaignMapOrder(tempMapOrder);
        }
      }
    }
  }
}

void Events::respondToPlayingGameEvents(sf::RenderWindow& window, sf::Event& evt) {
  if (Gui::isPlayingGame) {
    
    if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
      sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
      Utils util;
      if (Gui::consoleButtonPosition.contains(mousePosition)) {




		  UpdateLog("Events", "respondToSelectionBoxClick", "Play activated Console");



        ConsoleActions::initializeCharacterViews();
		ConsoleActions::consoleGameplayOptions();



        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::current_characters = util.readCurrentDirectoryContents("character");
      }
    }
    


    if (Gui::hasReachedEndOfMap) {
      cout << "reached end of map" << endl;
      Gui::hasReachedEndOfMap = false;
      Gui::GamePlayCurrentMap++;
      if (Gui::GamePlayCurrentMap != (int)GameData::currentCampaignObject->getCampaignMapOrder().size()) {

        Gui::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[Gui::GamePlayCurrentMap];
        MapCampaignFileIO mfio;
        mfio.readMapJSON(Gui::playedMap+".map");

        // Load all characters on new map;
        this->loadCharactersOnNewMap();

        // Level up every character in gameCharacters, by the number of GamePlayCurrentMap
        //
        //GameData::currentMapObject->setCurrentPosition();
      }
      else {
        cout << "!!! YOU WON THE CAMPAIGN !!!" << endl;
        exit(0);
      }
    }
  }
}

void Events::loadCharactersOnNewMap() {
  vector<tuple<char,int,int>> characterPositions = GameData::currentMapObject->getAllCharacterPositions();
  Gui::tempGameCharacters.clear();

  cout << "Going to check for existing chars in gameCharacters. its size: " << GameData::gameCharacters.size() << endl;

  for (int i = 0; i < (int)characterPositions.size(); i++) {
    for (int j = 0; j < (int)GameData::gameCharacters.size(); j++) {
      if (std::get<0>(characterPositions[i]) == 'S') {
        vector<int> currentPosition = {std::get<1>(characterPositions[i]), std::get<2>(characterPositions[i])};
        GameData::currentCharacterObject->setCurrentPosition(currentPosition);
        GameData::currentCharacterObject->setStrategy(new HumanPlayerStrategy());
        Gui::tempGameCharacters.push_back(GameData::currentCharacterObject);
        cout << "pushed back main character!" << endl;
      } else if (GameData::gameCharacters.size()>0 &&
          GameData::gameCharacters[i]->getTypeOnMap() == std::get<0>(characterPositions[i]) &&
          GameData::gameCharacters[i]->getCurrentPosition()[0] == std::get<1>(characterPositions[i]) &&
          GameData::gameCharacters[i]->getCurrentPosition()[1] == std::get<2>(characterPositions[i])) {
        vector<int> currentPosition = {std::get<1>(characterPositions[i]), std::get<2>(characterPositions[i])};
        GameData::gameCharacters[i]->setCurrentPosition(currentPosition);
        Gui::tempGameCharacters.push_back(GameData::gameCharacters[i]);
        cout << "pushed back existing character" << endl;
      }
    }
  }


  // Removed all gameCharacters that were not on the Map.
  GameData::gameCharacters = Gui::tempGameCharacters;

  cout << "size of gameCharacters" << GameData::gameCharacters.size() << endl;
  cout << GameData::gameCharacters[0]->getPlayerType() << endl;
  cout << GameData::gameCharacters[0]->getTypeOnMap() << endl;
  // Also need to scale each to the campaign level
  // Also need to make sure that the 'S' Character is always consistent across maps in campaign

  // Now add defaults for all that were not specified
  CharacterGenerator selectHero;
  CharacterBuilder* builder;
  for (int i = 0; i < (int)characterPositions.size(); i++) {
    bool shouldMakeDefaultChar = true;
    for (int j = 0; j < (int)GameData::gameCharacters.size(); j++) {
      cout << "About to test getTypeOnMap" << GameData::gameCharacters.size() << endl;
      if (GameData::gameCharacters[j]->getTypeOnMap() == std::get<0>(characterPositions[i]) &&
          GameData::gameCharacters[j]->getCurrentPosition()[0] == std::get<1>(characterPositions[i]) &&
          GameData::gameCharacters[j]->getCurrentPosition()[1] == std::get<2>(characterPositions[i])) {
        shouldMakeDefaultChar  = false;
      }
    }
    if (shouldMakeDefaultChar) {
      cout << "making default character" << GameData::gameCharacters.size() << endl;
      if (std::get<0>(characterPositions[i]) == 'C') {
        builder = new FriendlyCharacterBuilder("Nimble", 1); // Default is set to Nimble type and lvl1
        selectHero.setCharacterBuilder(builder);
        selectHero.createCharacter();
        Gui::tempCharacter = selectHero.getCharacter();
        vector<int> currentPosition = {std::get<1>(characterPositions[i]), std::get<2>(characterPositions[i])};
        Gui::tempCharacter->setCurrentPosition(currentPosition);
        Gui::tempCharacter->setTypeOnMap('C');
        Gui::tempGameCharacters.push_back(Gui::tempCharacter);
        GameData::gameCharacters.push_back(Gui::tempCharacter);
      }
      if (std::get<0>(characterPositions[i]) == 'O') {
        builder = new AggressorCharacterBuilder("Nimble", 1);
        selectHero.setCharacterBuilder(builder);
        selectHero.createCharacter();
        Gui::tempCharacter = selectHero.getCharacter();
        vector<int> currentPosition = {std::get<1>(characterPositions[i]), std::get<2>(characterPositions[i])};
        Gui::tempCharacter->setCurrentPosition(currentPosition);
        Gui::tempCharacter->setTypeOnMap('O');
        Gui::tempGameCharacters.push_back(Gui::tempCharacter);
        GameData::gameCharacters.push_back(Gui::tempCharacter);
      }
    }
  }

  cout << "Number of GameCharacters" << GameData::gameCharacters.size() << endl;


    //// ALSO CHECK FOR CHEST CONTENTS HERE

}


