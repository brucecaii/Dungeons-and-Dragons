//! @file
//! @brief Implementation file for the Events class
//!
#include <iostream>
#include <chrono>
#include <thread>
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

void Events::respondToSelectionBoxClick(sf::RenderWindow& window, sf::Event& evt) {
  if (evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left) {
    cout << "TEST" << endl;
    sf::Vector2f mousePosition(sf::Mouse::getPosition(window));
    Utils util;
    if (Gui::isSelectingChoice) {
      if (Gui::createMapPosition.contains(mousePosition)) {
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::isSelectingChoice = false;
        Gui::isChoosingMapToCreate = true;
      }
      if (Gui::editMapPosition.contains(mousePosition)) {
        Gui::current_maps = util.readCurrentDirectoryContents("map");
        Gui::isSelectingChoice = false;
        Gui::isChoosingMapToEdit = true;
      }
      if (Gui::createCampaignPosition.contains(mousePosition)) {
        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToCreate = true;
        Gui::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (Gui::editCampaignPosition.contains(mousePosition)) {
        Gui::current_campaigns = util.readCurrentDirectoryContents("campaign");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCampaignToEdit = true;
        Gui::current_maps = util.readCurrentDirectoryContents("map");
      }
      if (Gui::createCharacterPosition.contains(mousePosition)) {
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCharacterToCreate = true;
      }
      if (Gui::editCharacterPosition.contains(mousePosition)) {
        Gui::current_characters = util.readCurrentDirectoryContents("character");
        Gui::isSelectingChoice = false;
        Gui::isChoosingCharacterToEdit = true;

      }
      if (Gui::createItemPosition.contains(mousePosition)) {
        Gui::current_items = util.readCurrentDirectoryContents("item");
        Gui::isSelectingChoice = false;
        Gui::isChoosingItemToCreate = true;

      }
      if (Gui::editItemPosition.contains(mousePosition)) {
        Gui::current_items = util.readCurrentDirectoryContents("item");
        Gui::isSelectingChoice = false;
        Gui::isChoosingItemToEdit= true;
      }
      if (Gui::playPosition.contains(mousePosition)) {
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
          GameData::currentCharacterObject = new Character();
          GameData:: currentCharacterObject = cfio.readCharacter(Gui::chosenCharacter);
          Gui::shouldShowCharacterValidationError = false;
          Gui::isChoosingCharacterToEdit = false;
          Gui::isEditingCharacter = true;
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
          Gui::isChoosingCharacterToPlay = false;
          Gui::isPlayingGame = true;
          ///////////////////////////////////////////////////
          //   NEED BENNY LOGGER HERE                     //
          ///////////////////////////////////////////////////
          //GameData::currentCharacterObject->displayCharacter();
          Gui::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[Gui::GamePlayCurrentMap];
          MapCampaignFileIO mfio;
          mfio.readMapJSON(Gui::playedMap+".map");

          vector<tuple<char,int,int>> characterPositions = GameData::currentMapObject->getAllCharacterPositions();

          // As you read characters off the map, need to prompt user about type and level of character
          CharacterGenerator selectHero;
          for (int i = 0; i < (int)characterPositions.size(); i++) {
            // Create a new one with appropriate position and type
            char type; int posX; int posY;
            tie(type, posX, posY) = characterPositions[i];
            if (type == 'S') {
              cout << "There is a human character at position ("<< posX << ","<< posY <<")" << endl;
              cout << "Enter a CSV for type of fighter (Nimble/Tank/Bully) and Fighter level." << endl;
              cout << "Example: Bully,3" << endl;
              string answer;
              string delimeter(",");
              Utils util;
              getline(cin, answer);


              if (answer.find(delimeter) != string::npos) {
                vector<string> result;
                util.split(answer,delimeter.at(0), result);
                if ((int)result.size() == 2) {
                  //CharacterBuilder* playerBuilder = new PlayerCharacterBuilder("Bully", 2);
                  //selectHero.setCharacterBuilder(playerBuilder);
                  //selectHero.createCharacter();
                  //Character *player = selectHero.getCharacter();
                  vector<int> currentPosition = {posX,posY};
                  GameData::currentCharacterObject->setCurrentPosition(currentPosition);
                  GameData::currentCharacterObject->setStrategy(new HumanPlayerStrategy());
                  GameData::gameCharacters.push_back(GameData::currentCharacterObject);
                }
               }
            }
            if (type == 'C') {
              cout << "There is a friendly character at position ("<< posX << ","<< posY <<")" << endl;
              cout << "Enter a CSV for type of fighter (Nimble/Tank/Bully) and Fighter level." << endl;
              cout << "Example: Bully,3" << endl;
              string answer;
              string delimeter(",");
              Utils util;
              getline(cin, answer);


              if (answer.find(delimeter) != string::npos) {
                vector<string> result;
                util.split(answer,delimeter.at(0), result);
                if ((int)result.size() == 2) {
                CharacterBuilder* friendlyBuilder = new FriendlyCharacterBuilder("Tank", 4);
                selectHero.setCharacterBuilder(friendlyBuilder);
                selectHero.createCharacter();
                Character *friendly = selectHero.getCharacter();
                vector<int> currentPosition = {posX,posY};
                friendly->setCurrentPosition(currentPosition);
                GameData::gameCharacters.push_back(friendly);
                }
              }
            }
            if (type == 'O') {
              cout << "There is an aggressor character at position ("<< posX << ","<< posY <<")" << endl;
              cout << "Enter a CSV for type of fighter (Nimble/Tank/Bully) and Fighter level." << endl;
              cout << "Example: Bully,3" << endl;
              string answer;
              string delimeter(",");
              Utils util;
              getline(cin, answer);


              if (answer.find(delimeter) != string::npos) {
                vector<string> result;
                util.split(answer,delimeter.at(0), result);
                if ((int)result.size() == 2) {
                  CharacterBuilder* enermyBuilder = new EnermyCharacterBuilder("Nimble", 3);
                  selectHero.setCharacterBuilder(enermyBuilder);
                  selectHero.createCharacter();
                  Character *enermy = selectHero.getCharacter();
                  vector<int> currentPosition = {posX,posY};
                  enermy->setCurrentPosition(currentPosition);
                  GameData::gameCharacters.push_back(enermy);
                }
              }
            }
            // ALSO CHECK FOR CHEST CONTENTS HERE
          }
          cout << endl;

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

      if (Gui::isCreatingCharacter || Gui::isEditingCharacter) {

        /////////////////////////////////////////////////
        // NEED TO REDO CHARACTER EDITING AND CREATION //
        /////////////////////////////////////////////////

        //string args;
        //string tempCreatedArgs(Gui::createdCharacterArgs);
        //string tempChosenArgs(Gui::chosenCharacterArgs);
        //string fileNameOutput;
        //if (Gui::isCreatingCharacter) {
          //args = string(tempCreatedArgs);
          //fileNameOutput = Gui::createdCharacter;
        //}
        //if (Gui::isEditingCharacter) {
          //args = string(tempChosenArgs);
          //fileNameOutput = Gui::chosenCharacter;
        //}

        // check if csv is valid
        //Utils util;
        //util.removeSpaceCharFromString(args);
        //vector<string> stringArgElements;
        //vector<int> intArgElements;
        //util.split(args, ',', stringArgElements);

        //if (stringArgElements.size() != 6) {
          //cout << "INVALID: Must provide 6 ability values." << endl;
          //Gui::shouldShowCharacterValidationError = true;
          //return;
        //}

        //for (int i = 0; i < (int)stringArgElements.size(); i++) {
          //try {
            //intArgElements.push_back(stoi(stringArgElements[i]));
          //} catch (...) {
            ////string to int cast failed
            //cout << "INVALID: Ability values must be integers." << endl;
            //Gui::shouldShowCharacterValidationError = true;
            //return;
          //}
        //}

        // check if character is valid
        //GameData::currentCharacterObject = new Character(
          //intArgElements[0],
          //intArgElements[1],
          //intArgElements[2],
          //intArgElements[3],
          //intArgElements[4],
          //intArgElements[5]
        //);

        //// Character is valid
        //Gui::shouldShowCharacterValidationError = false;
        //CharacterFileIO cfio;
        //cfio.saveCharacter(fileNameOutput, *GameData::currentCharacterObject);
        //GameData::currentCharacterObject->displayCharacter();
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

    if (Gui::hasReachedEndOfMap) {
      Gui::hasReachedEndOfMap = false;
      Gui::GamePlayCurrentMap++;
      if (Gui::GamePlayCurrentMap != (int)GameData::currentCampaignObject->getCampaignMapOrder().size()) {
        GameData::currentCharacterObject->levelUp();
        //GameData::currentCharacterObject->displayCharacter();
        Gui::playedMap = GameData::currentCampaignObject->getCampaignMapOrder()[Gui::GamePlayCurrentMap];
        MapCampaignFileIO mfio;
        mfio.readMapJSON(Gui::playedMap+".map");
        //GameData::currentMapObject->setCurrentPosition();
      }
      else {
        cout << "!!! YOU WON THE CAMPAIGN !!!" << endl;
        exit(0);
      }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
      //GameData::currentMapObject->openChest();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
      //GameData::currentCharacterObject->displayCharacter();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
      //GameData::currentMapObject->moveLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
      //GameData::currentMapObject->moveRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
      //GameData::currentMapObject->moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
      //GameData::currentMapObject->moveDown();
    }
  }
}


