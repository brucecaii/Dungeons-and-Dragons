//! @file
//! @brief Implementation file for the Texts class
//!
#include <SFML/Graphics.hpp>
#include "Texts.h"
#include "Fonts.h"
#include "GuiData.h"

void Texts::generateEllipsis() {
  GuiData::ellipsis.setFont(GuiData::currentFont);
  GuiData::ellipsis.setString("...");
  GuiData::ellipsis.setCharacterSize(24);
  GuiData::ellipsis.setOrigin(GuiData::ellipsis.getGlobalBounds().width/2, GuiData::ellipsis.getGlobalBounds().height/2.0f);
  GuiData::ellipsis.setPosition(GuiData::WINDOW_WIDTH/2.0f, 0.0f);
  GuiData::ellipsis.setFillColor(GuiData::ELLIPSIS_COLOR);
}

void Texts::generateGreetings() {
  GuiData::greetings.setFont(GuiData::currentFont);
  GuiData::greetings.setString("Greetings, traveler.");
  GuiData::greetings.setCharacterSize(29);
  GuiData::greetings.setOrigin(GuiData::greetings.getGlobalBounds().width/2.0f, GuiData::greetings.getGlobalBounds().height/2.0f);
  GuiData::greetings.setPosition(GuiData::WINDOW_WIDTH/2.0f, 60.0f);
  GuiData::greetings.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
}

void Texts::generateCallToAction() {
  GuiData::callToAction.setFont(GuiData::currentFont);
  GuiData::callToAction.setString("What fate awaits you today?");
  GuiData::callToAction.setCharacterSize(24);
  GuiData::callToAction.setOrigin(GuiData::callToAction.getGlobalBounds().width/2.0f, GuiData::callToAction.getGlobalBounds().height/2.0f);
  GuiData::callToAction.setPosition(GuiData::WINDOW_WIDTH/2.0f, 120.0f);
  GuiData::callToAction.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
}

void Texts::generateSelectionBoxText(){
  GuiData::selectionBoxText.setFont(GuiData::currentFont);
  GuiData::selectionBoxText.setCharacterSize(24);
  GuiData::selectionBoxText.setOrigin(GuiData::selectionBoxText.getGlobalBounds().width/2.0f, GuiData::selectionBoxText.getGlobalBounds().height/2.0f);
  GuiData::selectionBoxText.setOutlineThickness(GuiData::TEXT_OUTLINE_THICKNESS);
}
