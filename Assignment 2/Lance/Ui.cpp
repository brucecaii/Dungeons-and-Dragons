//! @file
//! @brief Implementation file for the Ui class
//!
#include <chrono>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GuiData.h"
#include "Ui.h"

using std::cout;
using std::endl;

void Ui::updateTime() {
  unsigned long msTimeNow = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  GuiData::msSinceStart = msTimeNow - GuiData::UNIX_TIME_MS_START;
}

void Ui::drawEllipsis(sf::RenderWindow& window) {
  window.draw(GuiData::ellipsis);
}

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

void Ui::drawRealTimeTypeFeedback(sf::RenderWindow& window) {
  GuiData::realTimeTypeFeedback.setFont(GuiData::currentFont);
  GuiData::realTimeTypeFeedback.setCharacterSize(20);
  GuiData::realTimeTypeFeedback.setOrigin(GuiData::realTimeTypeFeedback.getGlobalBounds().width/2.0f, GuiData::realTimeTypeFeedback.getGlobalBounds().height/2.0f);
  GuiData::realTimeTypeFeedback.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
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




