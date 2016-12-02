//! @file
//! @brief Implementation file for the Ui class
//!
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "../GameData.h"
#include "Gui.h"
#include "Ui.h"
#include "../Map/MapCampaignFileIO.h"

using namespace std::chrono;

using std::cout;
using std::endl;
using std::to_string;

////////////////////////
// BASIC UI FUNCTIONS //
////////////////////////

// Draws some text and returns the position of its area on the screen
sf::FloatRect Ui::drawText(sf::RenderWindow& w, string s, int charSize, const sf::Color& c, float posX, float posY) {
  Gui::text.setFont(Gui::font);
  Gui::text.setString(s);
  Gui::text.setCharacterSize(charSize);
  Gui::text.setOrigin(Gui::text.getGlobalBounds().width/2, Gui::text.getGlobalBounds().height/2.0f);
  Gui::text.setPosition(posX, posY);
  Gui::text.setFillColor(c);
  w.draw(Gui::text);
  return Gui::text.getGlobalBounds();
}

// Draws a box and returns the position of its area on the screen
sf::FloatRect Ui::drawBox(sf::RenderWindow& w, float width, float height, const sf::Color& c, float posX, float posY) {
  Gui::box.setSize(sf::Vector2f(width, height));
  Gui::box.setFillColor(c);
  Gui::box.setOrigin(Gui::box.getGlobalBounds().width/2, Gui::box.getGlobalBounds().height/2.0f);
  Gui::box.setPosition(posX, posY);
  w.draw(Gui::box);
  return Gui::box.getGlobalBounds();
}

sf::FloatRect Ui::drawSprite(sf::RenderWindow& w, sf::Texture& t, float scaleX, float scaleY, float posX, float posY ) {
  Gui::sprite.setTexture(t);
  Gui::sprite.setOrigin(Gui::sprite.getGlobalBounds().width/2.0f, Gui::sprite.getGlobalBounds().height/2.0f);
  Gui::sprite.setColor(sf::Color(255, 255, 255));
  Gui::sprite.setScale(scaleX, scaleY);
  Gui::sprite.setPosition(posX, posY);
  w.draw(Gui::sprite);
  return Gui::sprite.getGlobalBounds();
}

////////////////////////////
// COMMON UTILITY METHODS //
////////////////////////////

//! Implementation of drawHomeButton, displays a link back the home page on most pages
void Ui::drawHomeButton(sf::RenderWindow& window) {
  Gui::homeButtonPosition = this->drawText(window, "<< HOME", 16, Gui::PINK, 60.0f, 30.0f);
}

void Ui::drawValidationErrorIfNeeded(sf::RenderWindow& window) {
  if (Gui::shouldShowMapValidationError)
    this->drawText(window, "MAP IS NOT VALID", 24, Gui::RED, Gui::W_WIDTH/2.0f, 50.0f);
  if (Gui::shouldShowCampaignValidationError)
    this->drawText(window, "CAMPAIGN IS NOT VALID", 24, Gui::RED, Gui::W_WIDTH/2.0f, 50.0f);
  if (Gui::shouldShowCharacterValidationError)
    this->drawText(window, "CHARACTER IS NOT VALID", 24, Gui::RED, Gui::W_WIDTH/2.0f, 50.0f);
  if (Gui::shouldShowItemValidationError)
    this->drawText(window, "ITEM IS NOT VALID", 24, Gui::RED, Gui::W_WIDTH/2.0f, 50.0f);
}

void Ui::drawSaveButton(sf::RenderWindow& window) {
  Gui::saveButtonPosition = this->drawText(window, "SAVE", 19, Gui::PINK, Gui::W_WIDTH-75.0f, 30.0f);
}

void Ui::drawMap(sf::RenderWindow& window) {
  Gui::box.setOutlineColor(Gui::PURPLE);
  Gui::box.setOutlineThickness(5.0f);
  Gui::mapBorderPosition = this->drawBox(window, Gui::MAP_DISPLAY_WIDTH_LENGTH, Gui::MAP_DISPLAY_WIDTH_LENGTH,
      Gui::LIGHT_GRAY, Gui::mapAbsolutePositioning.x, Gui::mapAbsolutePositioning.y);
  Gui::box.setOutlineColor(Gui::TRANSPARENT);
  Gui::box.setOutlineThickness(0.0f);

  int tempWidth = GameData::currentMapObject->getMapWidth();
  int tempLength = GameData::currentMapObject->getMapLength();
  float tempBoxWidth = Gui::MAP_DISPLAY_WIDTH_LENGTH/tempWidth;
  float tempBoxLength = Gui::MAP_DISPLAY_WIDTH_LENGTH/tempLength;
  sf::RectangleShape mapTile(sf::Vector2f(tempBoxWidth, tempBoxLength));
  sf::Color mapTileOutlineColor(248, 248, 242);
  mapTile.setFillColor(sf::Color::White);
  mapTile.setOutlineColor(mapTileOutlineColor);
  mapTile.setOutlineThickness(2.0f);

  Gui::currentMapTilePositions.resize(tempWidth);
  for (int i = 0; i < tempWidth; i++) {
    Gui::currentMapTilePositions[i].resize(tempLength);
    for (int j =0; j < tempLength; j++) {
      char tempMapCell = GameData::currentMapObject->getCell(i,j);

      if (tempMapCell == 'W') {
        mapTile.setTexture(&Gui::wallTexture);
      }
      else if (tempMapCell == 'S') {
        if (Gui::isCreatingMap || Gui::isEditingMap) {
          mapTile.setTexture(&Gui::startTexture);
        }
        if (Gui::isPlayingGame) {
          mapTile.setTexture(&Gui::characterTexture);
        }
      }
      else if (tempMapCell == 'E') {
        mapTile.setTexture(&Gui::exitTexture);
      }
      else if (tempMapCell == 'T') {
        mapTile.setTexture(&Gui::treasureTexture);
      }
      else if (tempMapCell == 'C') {
        mapTile.setTexture(&Gui::friendlyTexture);
      }
      else if (tempMapCell == 'O') {
        mapTile.setTexture(&Gui::monsterTexture);
      }
      else {
        mapTile.setTexture(&Gui::emptyTexture);
      }

      mapTile.setPosition(
          Gui::mapBorderPosition.left+ tempBoxWidth*i + 5,
          Gui::mapBorderPosition.top + tempBoxLength*j +5
      );

      Gui::currentMapTilePositions[i][j] = mapTile.getGlobalBounds();

      window.draw(mapTile);
    }
  }
}

//////////////////////////
// UI DRIVER FOR SCENES //
//////////////////////////

void Ui::isSelectingChoice(sf::RenderWindow& window) {
  this->drawText(window, "...", 24, Gui::PURPLE, Gui::W_WIDTH/2.0f, 0.0f);
  this->drawText(window, "Greetings, traveler.", 29, Gui::WHITE, Gui::W_WIDTH/2.0f, 60.0f);
  this->drawText(window, "What fate awaits you today?", 24, Gui::WHITE, Gui::W_WIDTH/2.0f, 120.0f);

  float selectionBoxWidth = 280.0f;
  float selectionBoxHeight = 85.0f;

  Gui::createMapPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, Gui::W_WIDTH/4.0f, 200.0f);
  Gui::editMapPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, 3*Gui::W_WIDTH/4.0f, 200.0f);
  Gui::createCampaignPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, Gui::W_WIDTH/4.0f, 300.0f);
  Gui::editCampaignPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, 3*Gui::W_WIDTH/4.0f, 300.0f);
  Gui::createCharacterPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, Gui::W_WIDTH/4.0f, 400.0f);
  Gui::editCharacterPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, 3*Gui::W_WIDTH/4.0f, 400.0f);
  Gui::createItemPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, Gui::W_WIDTH/4.0f, 500.0f);
  Gui::editItemPosition = this->drawBox(window, selectionBoxWidth, selectionBoxHeight, Gui::LIGHT_GRAY, 3*Gui::W_WIDTH/4.0f, 500.0f);
  Gui::playPosition = this->drawBox(window, selectionBoxWidth+50.0f, selectionBoxHeight+50.0f, Gui::LIGHT_GRAY, Gui::W_WIDTH/2.0f, 650.0f);

  this->drawText(window, "Create Map", 24, Gui::WHITE,
      Gui::createMapPosition.left + Gui::createMapPosition.width/2.0f,
      Gui::createMapPosition.top + Gui::createMapPosition.height/2.0f
  );
  this->drawText(window, "Edit Map", 24, Gui::WHITE,
      Gui::editMapPosition.left + Gui::editMapPosition.width/2.0f,
      Gui::editMapPosition.top + Gui::editMapPosition.height/2.0f
  );
  this->drawText(window, "Create Campaign", 24, Gui::WHITE,
      Gui::createCampaignPosition.left + Gui::createCampaignPosition.width/2.0f,
      Gui::createCampaignPosition.top + Gui::createCampaignPosition.height/2.0f
  );
  this->drawText(window, "Edit Campaign", 24, Gui::WHITE,
      Gui::editCampaignPosition.left + Gui::editCampaignPosition.width/2.0f,
      Gui::editCampaignPosition.top + Gui::editCampaignPosition.height/2.0f
  );
  this->drawText(window, "Create Character", 24, Gui::WHITE,
      Gui::createCharacterPosition.left + Gui::createCharacterPosition.width/2.0f,
      Gui::createCharacterPosition.top + Gui::createCharacterPosition.height/2.0f
  );
  this->drawText(window, "Edit Character", 24, Gui::WHITE,
      Gui::editCharacterPosition.left + Gui::editCharacterPosition.width/2.0f,
      Gui::editCharacterPosition.top + Gui::editCharacterPosition.height/2.0f
  );
  this->drawText(window, "Create Item", 24, Gui::WHITE,
      Gui::createItemPosition.left + Gui::createItemPosition.width/2.0f,
      Gui::createItemPosition.top + Gui::createItemPosition.height/2.0f
  );
  this->drawText(window, "Edit Item", 24, Gui::WHITE,
      Gui::editItemPosition.left + Gui::editItemPosition.width/2.0f,
      Gui::editItemPosition.top + Gui::editItemPosition.height/2.0f
  );
  this->drawText(window, "Play", 50, Gui::WHITE,
      Gui::playPosition.left + Gui::playPosition.width/2.0f,
      Gui::playPosition.top + Gui::playPosition.height/2.0f
  );
}

void Ui::isSelectingMapSize(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  Gui::mapCreateOkPosition = this->drawText(window, "OK", 18, Gui::PINK, Gui::W_WIDTH-30.0f, 30.0f);

  this->drawText(window, "Select a map size (min 4x4)", 24, Gui::WHITE, Gui::W_WIDTH/2.0f, 50.0f);

  // Map Width Controls
  this->drawText(window, "Width\n "+to_string(Gui::tempMapWidth), 19, Gui::WHITE, 125.0f, 260.0f);
  Gui::widthPlusPosition = this->drawText(window, "+", 60, Gui::PINK, 90.0f, 290.0f);
  Gui::widthMinusPosition = this->drawText(window, "-", 60, Gui::PINK, 160.0f, 280.0f);

  // Map Length Controls
  this->drawText(window, "Length\n "+to_string(Gui::tempMapLength), 19, Gui::WHITE, Gui::W_WIDTH-125.0f, 260.0f);
  Gui::lengthPlusPosition = this->drawText(window, "+", 60, Gui::PINK, Gui::W_WIDTH-160.0f, 290.0f);
  Gui::lengthMinusPosition = this->drawText(window, "-", 60, Gui::PINK, Gui::W_WIDTH-90.0f, 280.0f);
}

void Ui::isTypingNameToCreate(sf::RenderWindow& window){
  this->drawHomeButton(window);

  string instructions = "";
  string realTimeType = "";

  if (Gui::isChoosingMapToCreate) {
    instructions = "Type the name of a new map.\nPress Enter when done.";
    realTimeType = Gui::createdMap;
  }
  if (Gui::isChoosingCampaignToCreate) {
    instructions = "Type the name of a new campaign.\nPress Enter when done.";
    realTimeType = Gui::createdCampaign;
  }
  if (Gui::isChoosingCharacterToCreate) {
    instructions = "Type the name of a new character.\nPress Enter when done.";
    realTimeType = Gui::createdCharacter;
  }
  if (Gui::isChoosingItemToCreate) {
    instructions = "Type the name of a new item.\nPress Enter when done.";
    realTimeType = Gui::createdItem;
  }

  this->drawText(window, instructions, 24, Gui::WHITE, Gui::W_WIDTH/2.0f, 50.0f);
  this->drawText(window, realTimeType, 20, Gui::WHITE, Gui::W_WIDTH/2.0f, 150.0f);

  if (Gui::shouldShowNameConflictError)
    this->drawText(window, "File already exists. User a different name.", 24, Gui::RED, Gui::W_WIDTH/2.0f, 650.0f);

}

void Ui::isChoosingSomethingToEditOrPlay(sf::RenderWindow& window) {
  this->drawHomeButton(window);

  string instructions = "";
  vector<string> fileList;
  float firstFileHeight = 120.0f;
  float fileHeightIncrement = 30.0f;

  // Display instructions to user
  if (Gui::isChoosingMapToEdit) {
    instructions = "Select a map from the following list.";
    fileList = Gui::current_maps;
    Gui::current_map_positions.clear();
  }
  if (Gui::isChoosingCampaignToEdit || Gui::isChoosingCampaignToPlay) {
    instructions = "Select a campaign from the following list.";
    fileList = Gui::current_campaigns;
    Gui::current_campaign_positions.clear();
  }
  if (Gui::isChoosingCharacterToEdit || Gui::isChoosingCharacterToPlay) {
    instructions = "Select a character from the following list.";
    fileList = Gui::current_characters;
    Gui::current_character_positions.clear();
  }
  if (Gui::isChoosingItemToEdit) {
    instructions = "Select a item from the following list.";
    fileList = Gui::current_items;
    Gui::current_item_positions.clear();
  }

  this->drawText(window, instructions, 24, Gui::WHITE, Gui::W_WIDTH/2.0f, 50.0f);

  // Display clickable file list to user

  for (int i = 0; i < (int)fileList.size(); i++) {
    sf::FloatRect filePosition = this->drawText(window, fileList[i], 20, Gui::WHITE, Gui::W_WIDTH/2.0f, firstFileHeight);
    firstFileHeight += fileHeightIncrement;

    if (Gui::isChoosingMapToEdit)
      Gui::current_map_positions.push_back(filePosition);
    if (Gui::isChoosingCampaignToEdit || Gui::isChoosingCampaignToPlay)
      Gui::current_campaign_positions.push_back(filePosition);
    if (Gui::isChoosingCharacterToEdit || Gui::isChoosingCharacterToPlay)
      Gui::current_character_positions.push_back(filePosition);
    if (Gui::isChoosingItemToEdit)
      Gui::current_item_positions.push_back(filePosition);
  }

  if (Gui::shouldShowPlayerTypeError) {
    this->drawText(window, "ERROR: must select a Player type character.", 20, Gui::RED, Gui::W_WIDTH/2.0f, 750.0f);
  }

  this->drawValidationErrorIfNeeded(window);
}

void Ui::isCreatingOrEditingMap(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  this->drawSaveButton(window);

  // draw sprite menu to select
  Gui::wallSelectionSpritePosition = this->drawSprite(window, Gui::wallTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, Gui::W_HEIGHT-300);
  Gui::treasureSelectionSpritePosition = this->drawSprite(window, Gui::treasureTexture, 0.5f, 0.5f, Gui::W_WIDTH-40, Gui::W_HEIGHT-300);
  Gui::startSelectionSpritePosition = this->drawSprite(window, Gui::startTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, Gui::W_HEIGHT-360);
  Gui::exitSelectionSpritePosition = this->drawSprite(window, Gui::exitTexture, 0.5f, 0.5f, Gui::W_WIDTH-40, Gui::W_HEIGHT-360);
  Gui::emptySelectionSpritePosition = this->drawSprite(window, Gui::emptyTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, Gui::W_HEIGHT-240);
  Gui::monsterSelectionSpritePosition = this->drawSprite(window, Gui::monsterTexture, 0.5f, 0.5f, Gui::W_WIDTH-40, Gui::W_HEIGHT-240);
  Gui::friendlySelectionSpritePosition = this->drawSprite(window, Gui::friendlyTexture, 0.5f, 0.5f, Gui::W_WIDTH-70, Gui::W_HEIGHT-180);

  this->drawMap(window);

  // Show the currently selected map tile
  this->drawText(window, "Current\nMap Tile", 20, Gui::WHITE, Gui::W_WIDTH-70.0f, 130.0f);
  if (Gui::currentMapTileSelectedChar == ' ') {
    this->drawSprite(window, Gui::emptyTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'W') {
    this->drawSprite(window, Gui::wallTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'T') {
    this->drawSprite(window, Gui::treasureTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'O') {
    this->drawSprite(window, Gui::monsterTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'S') {
    this->drawSprite(window, Gui::startTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'E') {
    this->drawSprite(window, Gui::exitTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }
  if (Gui::currentMapTileSelectedChar == 'C') {
    this->drawSprite(window, Gui::friendlyTexture, 0.5f, 0.5f, Gui::W_WIDTH-100, 180);
  }

  this->drawValidationErrorIfNeeded(window);
}


void Ui::isCreatingOrEditingCampaign(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  this->drawSaveButton(window);
  this->drawText(window, "Available Maps\nClick to add", 24, Gui::PURPLE, Gui::W_WIDTH/4.0f, 100.0f);
  this->drawText(window, "Map Order\nClick to remove", 24, Gui::PURPLE, 3*Gui::W_WIDTH/4.0f, 100.0f);

  float mapPositionIncrement = 35.0f;

  // Draw availables to add to campaign
  Gui::current_available_map_positions.clear();
  for (int i = 0; i < (int)Gui::current_maps.size(); i++) {
    Gui::current_available_map_positions.push_back(
      this->drawText(window, Gui::current_maps[i], 20, Gui::WHITE, Gui::W_WIDTH/4.0f, 170.0f+(i*mapPositionIncrement))
    );
  }

  // Draw maps currently in selected campaign
  Gui::current_campaign_map_order_positions.clear();
  for (int i = 0; i < (int)GameData::currentCampaignObject->getCampaignMapOrder().size(); i++) {
    Gui::current_campaign_map_order_positions.push_back(
      this->drawText(window, GameData::currentCampaignObject->getCampaignMapOrder()[i],
        20, Gui::WHITE, 3*Gui::W_WIDTH/4.0f, 170.0f+(i*mapPositionIncrement))
    );
  }

  this->drawValidationErrorIfNeeded(window);
}

void Ui::isCreatingOrEditingItem(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  this->drawSaveButton(window);
  this->drawText(window,
      "Enter space-separated values of\nitemName,itemType,enhancementType,enhancementBonus\nExample\nJason'sMind,Helmet,wis,5",
      21, Gui::WHITE, Gui::W_WIDTH/2.0f, 100.0f);

  if (Gui::isCreatingItem)
    this->drawText(window, Gui::createdItemArgs, 26, Gui::WHITE, Gui::W_WIDTH/2.0f, 210.0f);
  if (Gui::isEditingItem)
    this->drawText(window, Gui::chosenItemArgs, 26, Gui::WHITE, Gui::W_WIDTH/2.0f, 210.0f);

  if (Gui::isEditingItem) {
  }
  this->drawValidationErrorIfNeeded(window);
}

void Ui::isCreatingOrEditingCharacter(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  this->drawSaveButton(window);
  this->drawText(window,
      "Enter fighter type (Tank, Nimble, Bully),\nfighter strategy (Player, Friendly, Aggressor) and \ncharacter level as a space-separated string",
      21, Gui::WHITE, Gui::W_WIDTH/2.0f, 100.0f);

  if (Gui::isCreatingCharacter)
    this->drawText(window, Gui::createdCharacterArgs, 26, Gui::WHITE, Gui::W_WIDTH/2.0f, 210.0f);
  if (Gui::isEditingCharacter)
    this->drawText(window, Gui::chosenCharacterArgs, 26, Gui::WHITE, Gui::W_WIDTH/2.0f, 210.0f);

    this->drawText(window, "Edit Character Items", 24, Gui::PINK, Gui::W_WIDTH/2.0f, 260.0f);
    this->drawText(window, "Available Items", 20, Gui::PINK, Gui::W_WIDTH/4.0f, 300.0f);
    this->drawText(window, "Equipped Items", 20, Gui::PINK, 3*Gui::W_WIDTH/4.0f, 300.0f);



  if (Gui::isEditingCharacter) {
    string temp = GameData::currentCharacterObject->getPlayerType();
    this->drawText(window, "type:"+temp, 26, Gui::WHITE, Gui::W_WIDTH/6.0f, 740.0f);
    this->drawText(window, "lvl:"+to_string(GameData::currentCharacterObject->getLevel()), 26,Gui::WHITE, 3*Gui::W_WIDTH/6.0f, 740.0f);
    this->drawText(window, "HP:"+to_string(GameData::currentCharacterObject->getHitPoint()), 26, Gui::WHITE, 5*Gui::W_WIDTH/6.0f, 740.0f);
    this->drawText(window, "AC:"+to_string(GameData::currentCharacterObject->getArmorClass()), 22, Gui::WHITE, 100.0f, 780.0f);
    this->drawText(window, "Str:"+to_string(GameData::currentCharacterObject->characterAttr->getStrength()), 22, Gui::WHITE, 200.0f, 780.0f);
    this->drawText(window, "Dex:"+to_string(GameData::currentCharacterObject->characterAttr->getDexterity()), 22, Gui::WHITE, 300.0f, 780.0f);
    this->drawText(window, "Con:"+to_string(GameData::currentCharacterObject->characterAttr->getConstitution()), 22, Gui::WHITE, 400.0f, 780.0f);
    this->drawText(window, "Int:"+to_string(GameData::currentCharacterObject->characterAttr->getIntelligence()), 22, Gui::WHITE, 500.0f, 780.0f);
    this->drawText(window, "Wis:"+to_string(GameData::currentCharacterObject->characterAttr->getWisdom()), 22, Gui::WHITE, 600.0f, 780.0f);
    this->drawText(window, "Cha:"+to_string(GameData::currentCharacterObject->characterAttr->getCharisma()), 22, Gui::WHITE, 700.0f, 780.0f);

  }
  this->drawValidationErrorIfNeeded(window);
}

void Ui::isPlayingGame(sf::RenderWindow& window) {
  this->drawHomeButton(window);
  this->drawMap(window);
  this->drawValidationErrorIfNeeded(window);
}

