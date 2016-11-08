//! @file
//! @brief Driver file to create and execute the test suite OR drive the main program
//!
//! This program is able to either:
//! - Drive the CppUnit test suite
//! - Drive the main map creation program.

#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "GuiData.h"
#include "Map.h"
#include "MapTest.h"
#include "Fonts.h"
#include "Events.h"
#include "Texts.h"

using namespace std::chrono;
using namespace std::this_thread;

using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::string;

//! main() function. Entry point of the program.
//! It parses the passed arguments and either does the following:
//! - Runs the test suite:
//! - Runs the main map creation program:
int main(int argc, char* argv[]) {

  // Checking if test command-line parameter was passed.
  if (argc > 1) {
    string testString(argv[1]);
    if (testString.compare("test") == 0) {
      MapTest mt;
      return mt.runTestSuite();
    }
  } else {

    GuiData::currentFont = GuiData::fontGenerator.generateFont("./fonts/EagleLake-Regular.ttf");
    GuiData::textGenerator.generateEllipsis();
    GuiData::textGenerator.generateGreetings();
    GuiData::textGenerator.generateCallToAction();
    GuiData::textGenerator.generateSelectionBoxText();

    // Launch window
    sf::RenderWindow window(sf::VideoMode(GuiData::WINDOW_HEIGHT, GuiData::WINDOW_WIDTH), "comp345build", sf::Style::Close | sf::Style::Titlebar);

    // Define selection box
    sf::RectangleShape selectionBox(sf::Vector2f(280.f, 180.0f));
    selectionBox.setOrigin(selectionBox.getGlobalBounds().width/2.0f, selectionBox.getGlobalBounds().height/2.0f);

    GuiData::emptyTexture.loadFromFile("textures/empty.png");
    GuiData::wallTexture.loadFromFile("textures/wall.png");
    GuiData::startTexture.loadFromFile("textures/start.png");
    GuiData::exitTexture.loadFromFile("textures/exit.png");
    GuiData::monsterTexture.loadFromFile("textures/monster.png");
    GuiData::treasureTexture.loadFromFile("textures/treasure.png");
    GuiData::characterTexture.loadFromFile("textures/character.png");

    ///////////////
    // GAME LOOP //
    ///////////////
    while (window.isOpen()) {
      sf::Event evt;
      while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
          window.close();
        }
        GuiData::eventManager.respondToRealTimeTypeFeedback(evt);
      }
      GuiData::eventManager.respondToSelectionBoxClick(window);
      GuiData::eventManager.respondToHomeButtonClick(window);
      GuiData::eventManager.respondToSaveMapCampaign(window);
      GuiData::eventManager.respondToFileSelectionClick(window);
      GuiData::eventManager.respondToWidthPlusClick(window);
      GuiData::eventManager.respondToWidthMinusClick(window);
      GuiData::eventManager.respondToLengthPlusClick(window);
      GuiData::eventManager.respondToLengthMinusClick(window);
      GuiData::eventManager.respondToMapCreateOkButton(window);
      GuiData::eventManager.respondToMapTileWallSelect(window);
      GuiData::eventManager.respondToMapTileCharacterSelect(window);
      GuiData::eventManager.respondToMapTileMonsterSelect(window);
      GuiData::eventManager.respondToMapTileStartSelect(window);
      GuiData::eventManager.respondToMapTileExitSelect(window);
      GuiData::eventManager.respondToMapTileTreasureSelect(window);
      GuiData::eventManager.respondToMapTileEmptySelect(window);

      // SCENE SELECTION
      window.clear(GuiData::SELECTION_BACKGROUND_COLOR);
      GuiData::uiManager.updateTime();

      if (GuiData::isSelectingChoice) {
        GuiData::uiManager.drawEllipsis(window);
        GuiData::uiManager.drawGreetings(window);
        GuiData::uiManager.drawCallToAction(window);
        GuiData::uiManager.drawSelectionBoxes(window, selectionBox);
      }
      if (GuiData::isSelectingMapSize) {
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawWidthIndicator(window);
        GuiData::uiManager.drawWidthPlus(window);
        GuiData::uiManager.drawWidthMinus(window);
        GuiData::uiManager.drawLengthIndicator(window);
        GuiData::uiManager.drawLengthPlus(window);
        GuiData::uiManager.drawLengthMinus(window);
        GuiData::uiManager.drawMapCreateOkButton(window);
        GuiData::uiManager.drawSelectMapSize(window);
      }

      if (GuiData::isChoosingMapToCreate || GuiData::isChoosingCampaignToCreate){
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawTypeMapCampaignName(window);
        GuiData::uiManager.drawRealTimeTypeFeedback(window);
        if (GuiData::shouldShowNameConflictError) {
          GuiData::uiManager.drawNameConflictError(window);
        }
      }
      if (GuiData::isChoosingMapToEdit){
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawSelectMapCampaign(window);
        GuiData::uiManager.drawSelectFileNames(window, GuiData::current_maps);
      }
      if (GuiData::isChoosingCampaignToEdit){
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawSelectMapCampaign(window);
        GuiData::uiManager.drawSelectFileNames(window, GuiData::current_campaigns);
      }
      if (GuiData::isEditingMap) {
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawMapUi(window);
        GuiData::uiManager.drawSaveButton(window);
        GuiData::uiManager.drawWallSpriteSelector(window);
        GuiData::uiManager.drawTreasureSpriteSelector(window);
        GuiData::uiManager.drawExitSpriteSelector(window);
        GuiData::uiManager.drawStartSpriteSelector(window);
        GuiData::uiManager.drawCharacterSpriteSelector(window);
        GuiData::uiManager.drawMonsterSpriteSelector(window);
        GuiData::uiManager.drawEmptySpriteSelector(window);
        GuiData::uiManager.drawMapBorder(window);
        GuiData::uiManager.drawMapClickableBox(window);
        GuiData::uiManager.drawCurrentMapTileSelected(window);
        GuiData::uiManager.drawCurrentMapTileSprite(window);
      }
      if (GuiData::isEditingCampaign) {
        GuiData::uiManager.drawHomeButton(window);
        // GuiData::uiManager.drawCampaignUi(window);
      }
      if (GuiData::isCreatingMap) {
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawMapUi(window);
        GuiData::uiManager.drawSaveButton(window);
        GuiData::uiManager.drawWallSpriteSelector(window);
        GuiData::uiManager.drawTreasureSpriteSelector(window);
        GuiData::uiManager.drawExitSpriteSelector(window);
        GuiData::uiManager.drawStartSpriteSelector(window);
        GuiData::uiManager.drawCharacterSpriteSelector(window);
        GuiData::uiManager.drawMonsterSpriteSelector(window);
        GuiData::uiManager.drawEmptySpriteSelector(window);
        GuiData::uiManager.drawMapBorder(window);
        GuiData::uiManager.drawMapClickableBox(window);
        GuiData::uiManager.drawCurrentMapTileSelected(window);
        GuiData::uiManager.drawCurrentMapTileSprite(window);
      }
      if (GuiData::isCreatingCampaign) {
        GuiData::uiManager.drawHomeButton(window);
        // GuiData::uiManager.drawCampaignUi(window);
      }

      window.display();

      // Prevent multiple consecutive clicks
      if (GuiData::shouldBlockThread) {
        sleep_for(milliseconds(GuiData::BLOCK_THREAD_WAIT_TIME));
        GuiData::shouldBlockThread = false;
      }
    }

    return 0;
  }
}
