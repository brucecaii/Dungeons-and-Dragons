//! @file
//! @brief Implementation file for the Ui class
//!
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "GuiData.h"
#include "Ui.h"
#include "MapCampaignFileIO.h"

using namespace std::chrono;

using std::cout;
using std::endl;
using std::to_string;

//! Implementation of updateTime, determines the tunning total of milliseconds since the launch of the program.
void Ui::updateTime() {
  unsigned long msTimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  GuiData::msSinceStart = msTimeNow - GuiData::UNIX_TIME_MS_START;
}

//! Implementation of drawEllipsis, displays ellipses
void Ui::drawEllipsis(sf::RenderWindow& window) {
  window.draw(GuiData::ellipsis);
}

//! Implementation of drawGreetings, displays the greeting text with a fade in
void Ui::drawGreetings(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::GREETINGS_APPEAR_TIME) {
    if ((int)GuiData::greetingsTransparency < 255) {
      GuiData::greetingsTransparency += GuiData::FADE_IN_STEP;
      sf::Color greetingsColor(248, 248, 242, (int)GuiData::greetingsTransparency);
      sf::Color greetingsOutlineColor(189, 147, 249, (int)GuiData::greetingsTransparency);
      GuiData::greetings.setFillColor(greetingsColor);
      GuiData::greetings.setOutlineColor(greetingsOutlineColor);
    }
    window.draw(GuiData::greetings);
  }
}

//! Implementation of drawCallToAction, displays the callToAction text with a fade in
void Ui::drawCallToAction(sf::RenderWindow& window) {
  if (GuiData::msSinceStart > GuiData::CALL_TO_ACTION_APPEAR_TIME) {
    if ((int)GuiData::callToActionTransparency < 255) {
      GuiData::callToActionTransparency += GuiData::FADE_IN_STEP;
      sf::Color callToActionColor(248, 248, 242, (int)GuiData::callToActionTransparency);
      sf::Color callToActionOutlineColor(189, 147, 249, (int)GuiData::callToActionTransparency);
      GuiData::callToAction.setFillColor(callToActionColor);
      GuiData::callToAction.setOutlineColor(callToActionOutlineColor);
    }
    window.draw(GuiData::callToAction);
  }
}

//! Implementation of drawSelectionBoxes, displays clickable boxes for the user to decide their initial action.
void Ui::drawSelectionBoxes(sf::RenderWindow& window, sf::RectangleShape& selectionBox) {
  if (GuiData::msSinceStart > GuiData::SELECTION_BOXES_APPEAR_TIME) {
    if ((int)GuiData::selectionBoxTransparency < 255) {
      GuiData::selectionBoxTransparency += GuiData::FADE_IN_STEP;
      sf::Color selectionBoxColor(68, 71, 90, (int)GuiData::selectionBoxTransparency);
      sf::Color selectionBoxTextColor(248, 248, 242, (int)GuiData::selectionBoxTransparency);
      sf::Color selectionBoxTextOutlineColor(189, 147, 249, (int)GuiData::selectionBoxTransparency);
      selectionBox.setFillColor(selectionBoxColor);
      GuiData::selectionBoxText.setFillColor(selectionBoxTextColor);
      GuiData::selectionBoxText.setOutlineColor(selectionBoxTextOutlineColor);
    }

    // Draw "Create Map" Box and record coordinates
    selectionBox.setPosition(200.0f, 300.0f);
    GuiData::selectionBoxText.setString("Create Map");
    GuiData::selectionBoxText.setPosition(125.0f, 285.0f);
    window.draw(selectionBox);
    window.draw(GuiData::selectionBoxText);
    if (!GuiData::hasCreateMapPosition){
      GuiData::createMapPosition = selectionBox.getGlobalBounds();
      GuiData::hasCreateMapPosition = true;
    }

    // Draw "Edit Map" Box and record coordinates
    selectionBox.setPosition(200.0f, 550.0f);
    GuiData::selectionBoxText.setString("Edit Map");
    GuiData::selectionBoxText.setPosition(140.0f, 535.0f);
    window.draw(selectionBox);
    window.draw(GuiData::selectionBoxText);
    if (!GuiData::hasEditMapPosition){
      GuiData::editMapPosition =selectionBox.getGlobalBounds();
      GuiData::hasEditMapPosition = true;
    }

    // Draw "Create Campaign" Box and record coordinates
    selectionBox.setPosition(600.0f, 300.0f);
    GuiData::selectionBoxText.setString("Create Campaign");
    GuiData::selectionBoxText.setPosition(485.0f, 285.0f);
    window.draw(selectionBox);
    window.draw(GuiData::selectionBoxText);
    if (!GuiData::hasCreateCampaignPosition){
      GuiData::createCampaignPosition = selectionBox.getGlobalBounds();
      GuiData::hasCreateCampaignPosition = true;
    }

    // Draw "Edit Campaign" Box and record coordinates
    selectionBox.setPosition(600.0f, 550.0f);
    GuiData::selectionBoxText.setString("Edit Campaign");
    GuiData::selectionBoxText.setPosition(485.0f, 535.0f);
    window.draw(selectionBox);
    window.draw(GuiData::selectionBoxText);
    if (!GuiData::hasEditCampaignPosition){
      GuiData::editCampaignPosition = selectionBox.getGlobalBounds();
      GuiData::hasEditCampaignPosition = true;
    }
  }
}

//! Implementation of drawSelectMapCampaign, displays header text for selecting a map or campaign from files on disk.
void Ui::drawSelectMapCampaign(sf::RenderWindow& window) {
  GuiData::selectMap.setFont(GuiData::currentFont);
  if (GuiData::isChoosingMapToEdit) {
    GuiData::selectMap.setString("Select a map from the following list.");
  }
  if (GuiData::isChoosingCampaignToEdit) {
    GuiData::selectMap.setString("Select a campaign from the following list.");
  }
  GuiData::selectMap.setCharacterSize(24);
  GuiData::selectMap.setOrigin(GuiData::selectMap.getGlobalBounds().width/2.0f, GuiData::selectMap.getGlobalBounds().height/2.0f);
  GuiData::selectMap.setPosition(GuiData::WINDOW_WIDTH/2.0f, 50.0f);
  GuiData::selectMap.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
  sf::Color selectMapColor(248, 248, 242);
  sf::Color selectMapOutlineColor(189, 147, 249);
  GuiData::selectMap.setFillColor(selectMapColor);
  GuiData::selectMap.setOutlineColor(selectMapOutlineColor);
  window.draw(GuiData::selectMap);
}

//! Implementation of drawTypeMapCampaignName, displays header text a new map or campaign.
void Ui::drawTypeMapCampaignName(sf::RenderWindow& window) {
  GuiData::typeMapName.setFont(GuiData::currentFont);
  if (GuiData::isChoosingMapToCreate) {
    GuiData::typeMapName.setString("Type the name of a new map.\nPress Enter when done.");
  }
  if (GuiData::isChoosingCampaignToCreate) {
    GuiData::typeMapName.setString("Type the name of a new campaign.\nPress Enter when done.");
  }
  GuiData::typeMapName.setCharacterSize(24);
  GuiData::typeMapName.setOrigin(GuiData::typeMapName.getGlobalBounds().width/2.0f, GuiData::typeMapName.getGlobalBounds().height/2.0f);
  GuiData::typeMapName.setPosition(GuiData::WINDOW_WIDTH/2.0f, 50.0f);
  GuiData::typeMapName.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
  sf::Color typeMapNameColor(248, 248, 242);
  sf::Color typeMapNameOutlineColor(189, 147, 249);
  GuiData::typeMapName.setFillColor(typeMapNameColor);
  GuiData::typeMapName.setOutlineColor(typeMapNameOutlineColor);
  window.draw(GuiData::typeMapName);
}

//! Implementation of drawSelectFileNames, displays text for selecting a map or campaign from files for each file of a specific type on disk.
void Ui::drawSelectFileNames(sf::RenderWindow& window, vector<string> current_files) {
  GuiData::selectFileNames.setFont(GuiData::currentFont);
  GuiData::selectFileNames.setCharacterSize(20);
  GuiData::selectFileNames.setOrigin(GuiData::selectFileNames.getGlobalBounds().width/2.0f, GuiData::selectFileNames.getGlobalBounds().height/2.0f);
  GuiData::selectFileNames.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
  sf::Color selectFileNamesColor(248, 248, 242);
  GuiData::selectFileNames.setFillColor(selectFileNamesColor);

  float firstFileHeight = 120.0f;
  float fileHeightIncrement = 30.0f;

  GuiData::current_map_positions.clear();
  GuiData::current_campaign_positions.clear();
  for (int i = 0; i < (int)current_files.size(); i++) {
    GuiData::selectFileNames.setString(current_files[i]);
    GuiData::selectFileNames.setPosition(GuiData::WINDOW_WIDTH/2.0f, firstFileHeight);
    firstFileHeight += fileHeightIncrement;

    if (GuiData::isChoosingMapToEdit) {
      GuiData::current_map_positions.push_back(GuiData::selectFileNames.getGlobalBounds());
    }
    if (GuiData::isChoosingCampaignToEdit) {
      GuiData::current_campaign_positions.push_back(GuiData::selectFileNames.getGlobalBounds());
    }
    window.draw(GuiData::selectFileNames);
  }
}

//! Implementation of drawRealTimeTypeFeedbac, displays text as the user type for a filename for a new map or campaign.
void Ui::drawRealTimeTypeFeedback(sf::RenderWindow& window) {
  GuiData::realTimeTypeFeedback.setFont(GuiData::currentFont);
  GuiData::realTimeTypeFeedback.setCharacterSize(20);
  GuiData::realTimeTypeFeedback.setOrigin(GuiData::realTimeTypeFeedback.getGlobalBounds().width/2.0f, GuiData::realTimeTypeFeedback.getGlobalBounds().height/2.0f);
  sf::Color realTimeTypeFeedbackColor(248, 248, 242);
  GuiData::realTimeTypeFeedback.setFillColor(realTimeTypeFeedbackColor);
  if (GuiData::isChoosingMapToCreate) {
    GuiData::realTimeTypeFeedback.setString(GuiData::createdMap);
  }
  if (GuiData::isChoosingCampaignToCreate) {
    GuiData::realTimeTypeFeedback.setString(GuiData::createdCampaign);
  }
  GuiData::realTimeTypeFeedback.setPosition(GuiData::WINDOW_WIDTH/2.0f, 150.0f);
  window.draw(GuiData::realTimeTypeFeedback);
}

//! Implementation of drawNameConflictError, displays error text is a file with that name already exists
void Ui::drawNameConflictError(sf::RenderWindow& window) {
  GuiData::NameConflictError.setFont(GuiData::currentFont);
  GuiData::NameConflictError.setCharacterSize(24);
  GuiData::NameConflictError.setOrigin(GuiData::NameConflictError.getGlobalBounds().width/2.0f, GuiData::NameConflictError.getGlobalBounds().height/2.0f);
  sf::Color NameConflictErrorColor(255, 85, 85);
  GuiData::NameConflictError.setFillColor(NameConflictErrorColor);
  GuiData::NameConflictError.setString("File already exists. Use a different name.");
  GuiData::NameConflictError.setPosition(GuiData::WINDOW_WIDTH/2.0f, 650.0f);
  window.draw(GuiData::NameConflictError);
}

//! Implementation of drawHomeButton, displays a link back the home page on most pages
void Ui::drawHomeButton(sf::RenderWindow& window) {
  GuiData::HomeButton.setFont(GuiData::currentFont);
  GuiData::HomeButton.setCharacterSize(19);
  GuiData::HomeButton.setOrigin(GuiData::HomeButton.getGlobalBounds().width/2.0f, GuiData::HomeButton.getGlobalBounds().height/2.0f);
  sf::Color HomeButtonColor(255, 121, 198);
  GuiData::HomeButton.setFillColor(HomeButtonColor);
  GuiData::HomeButton.setStyle(sf::Text::Bold);
  GuiData::HomeButton.setString("<< HOME");
  GuiData::HomeButton.setPosition(60.0f, 30.0f);
  window.draw(GuiData::HomeButton);
}

void Ui::drawMapUi(sf::RenderWindow& window) {
  // TBD
}

//! Implementation of drawWidthIndicator, displays the current map width while editing or creating a new map
void Ui::drawWidthIndicator(sf::RenderWindow& window) {
  GuiData::widthIndicator.setFont(GuiData::currentFont);
  GuiData::widthIndicator.setCharacterSize(19);
  GuiData::widthIndicator.setOrigin(GuiData::widthIndicator.getGlobalBounds().width/2.0f, GuiData::widthIndicator.getGlobalBounds().height/2.0f);
  sf::Color widthIndicatorColor(248, 248, 242);
  GuiData::widthIndicator.setFillColor(widthIndicatorColor);
  GuiData::widthIndicator.setString("Width\n "+to_string(GuiData::tempMapWidth));
  GuiData::widthIndicator.setPosition(125.0f, 260.0f);
  window.draw(GuiData::widthIndicator);
}

//! Implementation of drawWidthPlus, allows the user to increase map size
void Ui::drawWidthPlus(sf::RenderWindow& window) {
  GuiData::widthPlus.setFont(GuiData::currentFont);
  GuiData::widthPlus.setCharacterSize(40);
  GuiData::widthPlus.setOrigin(GuiData::widthPlus.getGlobalBounds().width/2.0f, GuiData::widthPlus.getGlobalBounds().height/2.0f);
  sf::Color widthPlusColor(255, 121, 198);
  GuiData::widthPlus.setFillColor(widthPlusColor);
  GuiData::widthPlus.setString("+");
  GuiData::widthPlus.setPosition(90.0f, 290.0f);
  window.draw(GuiData::widthPlus);
}

//! Implementation of drawWidthMinus, allows the user to decrease map size
void Ui::drawWidthMinus(sf::RenderWindow& window) {
  GuiData::widthMinus.setFont(GuiData::currentFont);
  GuiData::widthMinus.setCharacterSize(40);
  GuiData::widthMinus.setOrigin(GuiData::widthMinus.getGlobalBounds().width/2.0f, GuiData::widthMinus.getGlobalBounds().height/2.0f);
  sf::Color widthMinusColor(255, 121, 198);
  GuiData::widthMinus.setFillColor(widthMinusColor);
  GuiData::widthMinus.setString("-");
  GuiData::widthMinus.setPosition(160.0f, 280.0f);
  window.draw(GuiData::widthMinus);

}

//! Implementation of drawLengthIndicator, displays the current map length while editing or creating a new map
void Ui::drawLengthIndicator(sf::RenderWindow& window) {
  GuiData::lengthIndicator.setFont(GuiData::currentFont);
  GuiData::lengthIndicator.setCharacterSize(19);
  GuiData::lengthIndicator.setOrigin(GuiData::lengthIndicator.getGlobalBounds().width/2.0f, GuiData::lengthIndicator.getGlobalBounds().height/2.0f);
  sf::Color lengthIndicatorColor(248, 248, 242);
  GuiData::lengthIndicator.setFillColor(lengthIndicatorColor);
  GuiData::lengthIndicator.setString("Length\n "+to_string(GuiData::tempMapLength));
  GuiData::lengthIndicator.setPosition(GuiData::WINDOW_WIDTH-125.0f, 260.0f);
  window.draw(GuiData::lengthIndicator);
}

//! Implementation of drawLengthPlus, allows the user to increase map size
void Ui::drawLengthPlus(sf::RenderWindow& window) {
  GuiData::lengthPlus.setFont(GuiData::currentFont);
  GuiData::lengthPlus.setCharacterSize(40);
  GuiData::lengthPlus.setOrigin(GuiData::lengthPlus.getGlobalBounds().width/2.0f, GuiData::lengthPlus.getGlobalBounds().height/2.0f);
  sf::Color lengthPlusColor(255, 121, 198);
  GuiData::lengthPlus.setFillColor(lengthPlusColor);
  GuiData::lengthPlus.setString("+");
  GuiData::lengthPlus.setPosition(GuiData::WINDOW_WIDTH-160.0f, 290.0f);
  window.draw(GuiData::lengthPlus);
}

//! Implementation of drawLengthMinus, allows the user to decrease map size
void Ui::drawLengthMinus(sf::RenderWindow& window){
  GuiData::lengthMinus.setFont(GuiData::currentFont);
  GuiData::lengthMinus.setCharacterSize(40);
  GuiData::lengthMinus.setOrigin(GuiData::lengthMinus.getGlobalBounds().width/2.0f, GuiData::lengthMinus.getGlobalBounds().height/2.0f);
  sf::Color lengthMinusColor(255, 121, 198);
  GuiData::lengthMinus.setFillColor(lengthMinusColor);
  GuiData::lengthMinus.setString("-");
  GuiData::lengthMinus.setPosition(GuiData::WINDOW_WIDTH-90.0f, 280.0f);
  window.draw(GuiData::lengthMinus);
}

//! Implementation of drawSaveButton, allows the user to save a specific map or campaign to disk
void Ui::drawSaveButton(sf::RenderWindow& window) {
  GuiData::saveButton.setFont(GuiData::currentFont);
  GuiData::saveButton.setCharacterSize(19);
  GuiData::saveButton.setOrigin(GuiData::saveButton.getGlobalBounds().width/2.0f, GuiData::saveButton.getGlobalBounds().height/2.0f);
  sf::Color saveButtonColor(255, 121, 198);
  GuiData::saveButton.setFillColor(saveButtonColor);
  GuiData::saveButton.setStyle(sf::Text::Bold);
  GuiData::saveButton.setString("SAVE");
  GuiData::saveButton.setPosition(GuiData::WINDOW_WIDTH-75.0f, 30.0f);
  window.draw(GuiData::saveButton);
}

//! Implementation of drawWallSpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawWallSpriteSelector(sf::RenderWindow& window) {
  GuiData::wallSelectionSprite.setTexture(GuiData::wallTexture);
  GuiData::wallSelectionSprite.setOrigin(GuiData::wallSelectionSprite.getGlobalBounds().width/2.0f, GuiData::wallSelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::wallSelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::wallSelectionSprite.setScale(0.5f, 0.5f);
  GuiData::wallSelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 100, GuiData::WINDOW_HEIGHT - 300);
  window.draw(GuiData::wallSelectionSprite);
}

//! Implementation of drawTreasureSpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawTreasureSpriteSelector(sf::RenderWindow& window) {
  GuiData::treasureSelectionSprite.setTexture(GuiData::treasureTexture);
  GuiData::treasureSelectionSprite.setOrigin(GuiData::treasureSelectionSprite.getGlobalBounds().width/2.0f, GuiData::treasureSelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::treasureSelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::treasureSelectionSprite.setScale(0.5f, 0.5f);
  GuiData::treasureSelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 40, GuiData::WINDOW_HEIGHT - 300);
  window.draw(GuiData::treasureSelectionSprite);
}

//! Implementation of drawExitSpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawExitSpriteSelector(sf::RenderWindow& window) {
  GuiData::exitSelectionSprite.setTexture(GuiData::exitTexture);
  GuiData::exitSelectionSprite.setOrigin(GuiData::exitSelectionSprite.getGlobalBounds().width/2.0f, GuiData::exitSelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::exitSelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::exitSelectionSprite.setScale(0.5f, 0.5f);
  GuiData::exitSelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 40, GuiData::WINDOW_HEIGHT - 360);
  window.draw(GuiData::exitSelectionSprite);
}

//! Implementation of drawStartSpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawStartSpriteSelector(sf::RenderWindow& window) {
  GuiData::startSelectionSprite.setTexture(GuiData::startTexture);
  GuiData::startSelectionSprite.setOrigin(GuiData::startSelectionSprite.getGlobalBounds().width/2.0f, GuiData::startSelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::startSelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::startSelectionSprite.setScale(0.5f, 0.5f);
  GuiData::startSelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 100, GuiData::WINDOW_HEIGHT - 360);
  window.draw(GuiData::startSelectionSprite);
}

//! Implementation of drawMonsterSpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawMonsterSpriteSelector(sf::RenderWindow& window) {
  GuiData::monsterSelectionSprite.setTexture(GuiData::monsterTexture);
  GuiData::monsterSelectionSprite.setOrigin(GuiData::monsterSelectionSprite.getGlobalBounds().width/2.0f, GuiData::monsterSelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::monsterSelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::monsterSelectionSprite.setScale(0.5f, 0.5f);
  GuiData::monsterSelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 40, GuiData::WINDOW_HEIGHT - 240);
  window.draw(GuiData::monsterSelectionSprite);
}

//! Implementation of drawEmptySpriteSelector, shows a sprite icon available to select for placement on the map.
void Ui::drawEmptySpriteSelector(sf::RenderWindow& window) {
  GuiData::emptySelectionSprite.setTexture(GuiData::emptyTexture);
  GuiData::emptySelectionSprite.setOrigin(GuiData::emptySelectionSprite.getGlobalBounds().width/2.0f, GuiData::emptySelectionSprite.getGlobalBounds().height/2.0f);
  GuiData::emptySelectionSprite.setColor(sf::Color(255, 255, 255, 200));
  GuiData::emptySelectionSprite.setScale(0.5f, 0.5f);
  GuiData::emptySelectionSprite.setPosition(GuiData::WINDOW_WIDTH - 100, GuiData::WINDOW_HEIGHT - 240);
  window.draw(GuiData::emptySelectionSprite);
}
//! Implementation of drawMapBorder, shows a box around the area where the map is displayed.
void Ui::drawMapBorder(sf::RenderWindow& window) {
  sf::RectangleShape mapBorder(sf::Vector2f(GuiData::MAP_DISPLAY_WIDTH_LENGTH, GuiData::MAP_DISPLAY_WIDTH_LENGTH));
  sf::Color mapBorderColor(68, 71, 90);
  sf::Color mapBorderOutlineColor(189, 147, 249);
  mapBorder.setFillColor(mapBorderColor);
  mapBorder.setOutlineColor(mapBorderOutlineColor);
  mapBorder.setOutlineThickness(5.0f);
  mapBorder.setPosition(GuiData::mapAbsolutePositioning);
  window.draw(mapBorder);
}

void Ui::drawMapClickableBox(sf::RenderWindow& window) {
  int tempWidth = GameData::currentMapObject->getMapWidth();
  int tempLength = GameData::currentMapObject->getMapLength();
  float tempBoxWidth = GuiData::MAP_DISPLAY_WIDTH_LENGTH/tempWidth;
  float tempBoxLength = GuiData::MAP_DISPLAY_WIDTH_LENGTH/tempLength;
  sf::RectangleShape mapClickableBox(sf::Vector2f(tempBoxWidth, tempBoxLength));
  sf::Color mapClickableBoxOutlineColor(248, 248, 242);
  mapClickableBox.setFillColor(sf::Color::White);
  mapClickableBox.setOutlineColor(mapClickableBoxOutlineColor);
  mapClickableBox.setOutlineThickness(2.0f);

  GuiData::currentMapTilePositions.resize(tempWidth);
  for (int i = 0; i < tempWidth; i++) {
    GuiData::currentMapTilePositions[i].resize(tempLength);
    for (int j =0; j < tempLength; j++) {
      char tempMapCell = GameData::currentMapObject->getCell(i,j);

      if (tempMapCell == 'W') {
        mapClickableBox.setTexture(&GuiData::wallTexture);
      }
      else if (tempMapCell == 'S') {
        mapClickableBox.setTexture(&GuiData::startTexture);
      }
      else if (tempMapCell == 'E') {
        mapClickableBox.setTexture(&GuiData::exitTexture);
      }
      else if (tempMapCell == 'T') {
        mapClickableBox.setTexture(&GuiData::treasureTexture);
      }
      else if (tempMapCell == 'O') {
        mapClickableBox.setTexture(&GuiData::monsterTexture);
      }
      else {
        mapClickableBox.setTexture(&GuiData::emptyTexture);
      }

      mapClickableBox.setPosition(
          GuiData::mapAbsolutePositioning.x + tempBoxWidth*i,
          GuiData::mapAbsolutePositioning.y + tempBoxLength*j
      );

      GuiData::currentMapTilePositions[i][j] = mapClickableBox.getGlobalBounds();

      window.draw(mapClickableBox);
    }
  }
}
void Ui::drawMapCreateOkButton(sf::RenderWindow& window) {
  GuiData::mapCreateOkButton.setFont(GuiData::currentFont);
  GuiData::mapCreateOkButton.setCharacterSize(19);
  GuiData::mapCreateOkButton.setOrigin(GuiData::mapCreateOkButton.getGlobalBounds().width/2.0f, GuiData::mapCreateOkButton.getGlobalBounds().height/2.0f);
  sf::Color mapCreateOkButtonColor(255, 121, 198);
  GuiData::mapCreateOkButton.setFillColor(mapCreateOkButtonColor);
  GuiData::mapCreateOkButton.setStyle(sf::Text::Bold);
  GuiData::mapCreateOkButton.setString("OK");
  GuiData::mapCreateOkButton.setPosition(GuiData::WINDOW_WIDTH-75.0f, 30.0f);
  window.draw(GuiData::mapCreateOkButton);
}

void Ui::drawSelectMapSize(sf::RenderWindow& window) {
  GuiData::selectMapSize.setString("Select a map size (min 4x4)");
  GuiData::selectMapSize.setFont(GuiData::currentFont);
  GuiData::selectMapSize.setCharacterSize(24);
  GuiData::selectMapSize.setOrigin(GuiData::selectMapSize.getGlobalBounds().width/2.0f, GuiData::selectMapSize.getGlobalBounds().height/2.0f);
  GuiData::selectMapSize.setPosition(GuiData::WINDOW_WIDTH/2.0f, 50.0f);
  GuiData::selectMapSize.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
  sf::Color selectMapSizeColor(248, 248, 242);
  sf::Color selectMapSizeOutlineColor(189, 147, 249);
  GuiData::selectMapSize.setFillColor(selectMapSizeColor);
  GuiData::selectMapSize.setOutlineColor(selectMapSizeOutlineColor);
  window.draw(GuiData::selectMapSize);
}

void Ui::drawCurrentMapTileSelected(sf::RenderWindow& window) {
  GuiData::currentMapTileSelected.setString("Current\nMap Tile");
  GuiData::currentMapTileSelected.setFont(GuiData::currentFont);
  GuiData::currentMapTileSelected.setCharacterSize(20);
  GuiData::currentMapTileSelected.setOrigin(GuiData::currentMapTileSelected.getGlobalBounds().width/2.0f, GuiData::currentMapTileSelected.getGlobalBounds().height/2.0f);
  GuiData::currentMapTileSelected.setPosition(GuiData::WINDOW_WIDTH-70.0f, 130.0f);
  sf::Color currentMapTileSelectedColor(248, 248, 242);
  GuiData::currentMapTileSelected.setFillColor(currentMapTileSelectedColor);
  window.draw(GuiData::currentMapTileSelected);
}

//! Implementation of drawCurrentMapTileSelectedBox, shows the currently selected sprite icon.
void Ui::drawCurrentMapTileSprite(sf::RenderWindow& window) {
  sf::Sprite currentMapTileSprite;
  currentMapTileSprite.setOrigin(currentMapTileSprite.getGlobalBounds().width/2.0f, currentMapTileSprite.getGlobalBounds().height/2.0f);
  currentMapTileSprite.setColor(sf::Color::White);
  currentMapTileSprite.setScale(0.5f, 0.5f);
  currentMapTileSprite.setPosition(GuiData::WINDOW_WIDTH - 100, 180);

  if (GuiData::currentMapTileSelectedChar == ' ') {
    currentMapTileSprite.setTexture(GuiData::emptyTexture);
  }
  if (GuiData::currentMapTileSelectedChar == 'W') {
    currentMapTileSprite.setTexture(GuiData::wallTexture);
  }
  if (GuiData::currentMapTileSelectedChar == 'T') {
    currentMapTileSprite.setTexture(GuiData::treasureTexture);
  }
  if (GuiData::currentMapTileSelectedChar == 'O') {
    currentMapTileSprite.setTexture(GuiData::monsterTexture);
  }
  if (GuiData::currentMapTileSelectedChar == 'S') {
    currentMapTileSprite.setTexture(GuiData::startTexture);
  }
  if (GuiData::currentMapTileSelectedChar == 'E') {
    currentMapTileSprite.setTexture(GuiData::exitTexture);
  }

  window.draw(currentMapTileSprite);

}

void Ui::drawCampaignAvailableMapsText(sf::RenderWindow& window) {
  GuiData::campaignAvailableMapsText.setString("Availble Maps\nClick to add");
  GuiData::campaignAvailableMapsText.setFont(GuiData::currentFont);
  GuiData::campaignAvailableMapsText.setCharacterSize(24);
  GuiData::campaignAvailableMapsText.setOrigin(GuiData::campaignAvailableMapsText.getGlobalBounds().width/2.0f, GuiData::campaignAvailableMapsText.getGlobalBounds().height/2.0f);
  GuiData::campaignAvailableMapsText.setPosition(GuiData::WINDOW_WIDTH/4.0f, 100.0f);
  sf::Color campaignAvailableMapsTextColor(189, 147, 249);
  GuiData::campaignAvailableMapsText.setFillColor(campaignAvailableMapsTextColor);
  window.draw(GuiData::campaignAvailableMapsText);
}

void Ui::drawCampaignMapOrderText(sf::RenderWindow& window) {
  GuiData::campaignMapOrderText.setString("Map Order\nClick to remove");
  GuiData::campaignMapOrderText.setFont(GuiData::currentFont);
  GuiData::campaignMapOrderText.setCharacterSize(24);
  GuiData::campaignMapOrderText.setOrigin(GuiData::campaignMapOrderText.getGlobalBounds().width/2.0f, GuiData::campaignMapOrderText.getGlobalBounds().height/2.0f);
  GuiData::campaignMapOrderText.setPosition(GuiData::WINDOW_WIDTH*3/4.0f, 100.0f);
  sf::Color campaignMapOrderTextColor(189, 147, 249);
  GuiData::campaignMapOrderText.setFillColor(campaignMapOrderTextColor);
  window.draw(GuiData::campaignMapOrderText);
}

void Ui::drawCampaignAvailableMaps(sf::RenderWindow& window) {
  GuiData::campaignAvailableMaps.setFont(GuiData::currentFont);
  GuiData::campaignAvailableMaps.setCharacterSize(20);
  GuiData::campaignAvailableMaps.setOrigin(GuiData::campaignAvailableMaps.getGlobalBounds().width/2.0f, GuiData::campaignAvailableMaps.getGlobalBounds().height/2.0f);
  sf::Color campaignAvailableMapsColor(248,248,242);
  GuiData::campaignAvailableMaps.setFillColor(campaignAvailableMapsColor);

  float mapPositionIncrement = 35.0f;
  GuiData::current_available_map_positions.clear();
  for (int i = 0; i < (int)GuiData::current_maps.size(); i++) {
    GuiData::campaignAvailableMaps.setString(GuiData::current_maps[i]);
    GuiData::campaignAvailableMaps.setPosition(GuiData::WINDOW_WIDTH/4.0f, 170.0f+(i*mapPositionIncrement));
    GuiData::current_available_map_positions.push_back(GuiData::campaignAvailableMaps.getGlobalBounds());
    window.draw(GuiData::campaignAvailableMaps);
  }
}

void Ui::drawCampaignMapOrder(sf::RenderWindow& window) {
  GuiData::campaignMapOrder.setFont(GuiData::currentFont);
  GuiData::campaignMapOrder.setCharacterSize(20);
  GuiData::campaignMapOrder.setOrigin(GuiData::campaignMapOrder.getGlobalBounds().width/2.0f, GuiData::campaignMapOrder.getGlobalBounds().height/2.0f);
  sf::Color campaignMapOrderColor(248,248,242);
  GuiData::campaignMapOrder.setFillColor(campaignMapOrderColor);

  float mapPositionIncrement = 35.0f;
  GuiData::current_campaign_map_order_positions.clear();
  for (int i = 0; i < (int)GameData::currentCampaignObject->getCampaignMapOrder().size(); i++) {
    GuiData::campaignMapOrder.setString(GameData::currentCampaignObject->getCampaignMapOrder()[i]);
    GuiData::campaignMapOrder.setPosition(GuiData::WINDOW_WIDTH*3/4.0f, 170.0f+(i*mapPositionIncrement));
    GuiData::current_campaign_map_order_positions.push_back(GuiData::campaignMapOrder.getGlobalBounds());
    window.draw(GuiData::campaignMapOrder);
  }
}

