//! @file
//! @brief Driver file to drive the main program
//!
//! This program is able to either:
//! - Drive the main map creation program.

#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "Gui.h"
#include "Map.h"
#include "Fonts.h"
#include "Events.h"

using namespace std::chrono;
using namespace std::this_thread;

using std::cerr;
using std::cout;
using std::cin;
using std::endl;
using std::string;

//! main() function. Entry point of the program.
//! Runs the main map creation program:
int main(int argc, char* argv[]) {

    ///////////////////////////
    // INITIALIZING GUI DATA //
    ///////////////////////////

    Gui::font = Gui::fontGenerator.generateFont("./fonts/EagleLake-Regular.ttf");

    sf::RenderWindow window(sf::VideoMode(Gui::W_HEIGHT, Gui::W_WIDTH), "comp345build", sf::Style::Close | sf::Style::Titlebar);

    Gui::emptyTexture.loadFromFile("textures/empty.png");
    Gui::wallTexture.loadFromFile("textures/wall.png");
    Gui::startTexture.loadFromFile("textures/start.png");
    Gui::exitTexture.loadFromFile("textures/exit.png");
    Gui::monsterTexture.loadFromFile("textures/monster.png");
    Gui::treasureTexture.loadFromFile("textures/treasure.png");
    Gui::characterTexture.loadFromFile("textures/character.png");

    ///////////////
    // GAME LOOP //
    ///////////////
    while (window.isOpen()) {
      window.clear(Gui::DARK_GRAY);

      //////////////////////
      // EVENT MANAGEMENT //
      //////////////////////
      sf::Event evt;
      while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
          window.close();
        }
        Gui::eventManager.respondToRealTimeTypeFeedback(evt);
      }
      Gui::eventManager.respondToSelectionBoxClick(window);
      Gui::eventManager.respondToHomeButtonClick(window);
      Gui::eventManager.respondToSaveMapCampaign(window);
      Gui::eventManager.respondToFileSelectionClick(window);
      Gui::eventManager.respondToMapSizeClick(window);
      Gui::eventManager.respondToMapCreateOkButton(window);
      Gui::eventManager.respondToMapTileSelect(window);
      Gui::eventManager.respondToCampaignAvailableMapsClick(window);
      Gui::eventManager.respondToCampaignMapOrderClick(window);
      Gui::eventManager.respondToPlayingGameEvents(window);

      /////////////////////
      // SCENE SELECTION //
      /////////////////////
      if (Gui::isSelectingChoice)
        Gui::uiManager.isSelectingChoice(window);

      if (Gui::isSelectingMapSize)
        Gui::uiManager.isSelectingMapSize(window);

      if (Gui::isChoosingMapToCreate || Gui::isChoosingCampaignToCreate ||
          Gui::isChoosingCharacterToCreate || Gui::isChoosingItemToCreate) {
        Gui::uiManager.isTypingNameToCreate(window);
      }

      if (Gui::isChoosingMapToEdit || Gui::isChoosingCampaignToEdit ||
          Gui::isChoosingCharacterToEdit || Gui::isChoosingItemToEdit ||
          Gui::isChoosingCharacterToPlay || Gui::isChoosingCampaignToPlay ||
          Gui::isChoosingCampaignToPlay || Gui::isChoosingCharacterToPlay) {
        Gui::uiManager.isChoosingSomethingToEditOrPlay(window);
      }
      if (Gui::isEditingMap || Gui::isCreatingMap) {
        Gui::uiManager.isCreatingOrEditingMap(window);
        Gui::eventManager.respondToMapBoxClick(window);
      }
      if (Gui::isCreatingCampaign || Gui::isEditingCampaign) {
        Gui::uiManager.isCreatingOrEditingCampaign(window);
      }

      if (Gui::isCreatingCharacter || Gui::isEditingCharacter) {
        Gui::uiManager.isCreatingOrEditingCharacter(window);
      }
      if (Gui::isPlayingGame) {
        Gui::uiManager.isPlayingGame(window);
      }

      window.display();

      // Prevent multiple consecutive clicks
      if (Gui::shouldBlockThread) {
        sleep_for(milliseconds(Gui::BLOCK_THREAD_WAIT_TIME));
        Gui::shouldBlockThread = false;
      }
    }

    return 0;
}
