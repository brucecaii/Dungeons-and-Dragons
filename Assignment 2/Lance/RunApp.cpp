//! @file
//! @brief Driver file to create and execute the test suite OR drive the main program
//!
//! This program is able to either:
//! - Drive the CppUnit test suite
//! - Drive the main map creation program.
//!
//! If you want to *run the test suite*:
//! - Compile the program using the following g++ command on Linux:
//!   - `g++ -g -o comp345build RunApp.cpp MapTest.cpp Map.cpp /usr/lib/libcppunit.so`
//! - Generate the documentation:
//!    - `doxygen`
//! - Run the executable with the test argument:
//!   - ./comp345build test
//!
//! If you want to *run the map creation program*:
//! - Compile the program using the following g++ command on Linux:
//!   - `g++ -g -o comp345build RunApp.cpp MapTest.cpp Map.cpp /usr/lib/libcppunit.so`
//! - Generate the documentation:
//!    - `doxygen`
//! - Run the executable directly:
//!   - ./comp345build
//!
//! If you want to *view the Doxygen documentation*:
//! - Run a static web server in the html/ directory. For example:
//!   - cd html/ && python3 -m http.server
//!   - visit http://localhost:8000 in the browser.

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


// Free functions
// Main Driver helpers

//! Implementation of getSizeInput, prompts the user to enter the size of a map dimension to be stored.
//! @param size: an integer reference of the map's grid size
//! @param type: an string allowing for the prompt to the user for the right map dimension
//void getSizeInput(int& size, string type){
  //cout << "Enter a map " << type << " (greater than 1): ";
  //cin >> size;
  //if (size < 2) {
    //cout << "You did not enter an integer greater than 1. Defaulting to 5." << endl;
    //size = 5;
  //}
//}


//! Implementation of startMapMaking, initializes the map and provides instructions to the user.
//! @return pointer to Map object on the heap for further manipulation
//Map* startMapMaking() {
  //int width = 0;
  //int length = 0;
  //cout << "Welcome to DnD Map Maker, adventurer!" << endl;

  //getSizeInput(width, "width");
  //getSizeInput(length, "length");
  //Map* m = new Map(width, length);

  //// Initially display map and instructions
  //cout << endl;
  //cout << "This is a vast wasteland (empty map)." << endl;
  //m->displayMap();
  //cout << "The 'origin' of the map is in the top left corner at (0,0)." << endl;
  //cout << "This maps allows placement of walls (W), start doors (S), end doors (E). characters (C), treasure chests (T) and opponents (O)." << endl;
  //cout << "Valid maps are ones with a closed wall, at least two doors attached, and a clear path between these doors." << endl;
  //cout << "As an example, by entering the string 'W12', you place a wall at 1 position to the *RIGHT* and 2 positions *DOWN*." << endl;
  //cout << "The program *will not respond* if your input is not properly formatted." << endl;
  //cout << "You can also enter 'reset' to start over again, 'validate' to check the map for errors or 'quit' to exit the program. Have fun!" << endl;
  //cout << endl;
  //return m;
//}



//! main() function. Entry point of the program.
//! It parses the passed arguments and either does the following:
//! - Runs the test suite:
//! - Runs the main map creation program:
int main(int argc, char* argv[]) {

  // Checking if test command-line parameter was passed.
  if (argc > 1) {
    string testString(argv[1]);
    if (testString.compare("test") == 0) {
      //MapTest mt;
      //return mt.runTestSuite();
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

      // SCENE SELECTION
      window.clear(GuiData::SELECTION_BACKGROUND_COLOR);
      GuiData::uiManager.updateTime();

      if (GuiData::isSelectingChoice) {
        GuiData::uiManager.drawEllipsis(window);
        GuiData::uiManager.drawGreetings(window);
        GuiData::uiManager.drawCallToAction(window);
        GuiData::uiManager.drawSelectionBoxes(window, selectionBox);
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
        GuiData::uiManager.drawWidthIndicator(window);
        GuiData::uiManager.drawWidthPlus(window);
        GuiData::uiManager.drawWidthMinus(window);
        GuiData::uiManager.drawLengthIndicator(window);
        GuiData::uiManager.drawLengthPlus(window);
        GuiData::uiManager.drawLengthMinus(window);
        GuiData::uiManager.drawSaveButton(window);

      }
      if (GuiData::isEditingCampaign) {
        GuiData::uiManager.drawHomeButton(window);
        // GuiData::uiManager.drawCampaignUi(window);
      }
      if (GuiData::isCreatingMap) {
        GuiData::uiManager.drawHomeButton(window);
        GuiData::uiManager.drawMapUi(window);
        GuiData::uiManager.drawWidthIndicator(window);
        GuiData::uiManager.drawWidthPlus(window);
        GuiData::uiManager.drawWidthMinus(window);
        GuiData::uiManager.drawLengthIndicator(window);
        GuiData::uiManager.drawLengthPlus(window);
        GuiData::uiManager.drawLengthMinus(window);
        GuiData::uiManager.drawSaveButton(window);
        GuiData::uiManager.drawWallSpriteSelector(window);
        GuiData::uiManager.drawTreasureSpriteSelector(window);
        GuiData::uiManager.drawExitSpriteSelector(window);
        GuiData::uiManager.drawStartSpriteSelector(window);
        GuiData::uiManager.drawCharacterSpriteSelector(window);
        GuiData::uiManager.drawMonsterSpriteSelector(window);
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




    // Initalize map and provide instructions
    //Map* m = startMapMaking();

    // Game Loop
    //string input;
    //while (true) {
      // Get user input and analyze response for valid choices
      //cout << "$ ";
      //getline(cin, input);

      //if (input.compare("quit") == 0) {
        //// delete heap-allocated memory and fix dangling pointer, then quit.
        //delete m;
        //m = NULL;
        //cout << "Farewell, mere mortal." << endl;
        //exit(0);
        //continue;
      //}

      //if (input.compare("reset") == 0) {
        //cout << "Resetting map making session..." << endl;
        //startMapMaking();
      //}
      //if (input.compare("validate") == 0) {
        //cout << "Checking map validity..." << endl;
        //m->validatePath();
      //}

      //if (input.length() == 3 && input.find_first_of("WSECTO ") == 0) {
        //int xpos = input.at(1) - '0';
        //int ypos = input.at(2) - '0';
        //if (xpos >= 0 && ypos >= 0 && xpos < m->getMapWidth() && ypos < m->getMapLength()) {
          //m->fillCell(ypos, xpos, input.at(0));
          //m->displayMap();
        //}
      //}
    //}
    return 0;
  }
}
