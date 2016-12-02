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

#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <string>
#include "Map.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


// Free functions
// Main Driver helpers

//! Implementation of getSizeInput, prompts the user to enter the size of a map dimension to be stored.
//! @param size: an integer reference of the map's grid size
//! @param type: an string allowing for the prompt to the user for the right map dimension
void getSizeInput(int& size, string type){
  cout << "Enter a map " << type << " (greater than 1): ";
  cin >> size;
  if (size < 2) {
    cout << "You did not enter an integer greater than 1. Defaulting to 5." << endl;
    size = 5;
  }
}


//! Implementation of startMapMaking, initializes the map and provides instructions to the user.
//! @return pointer to Map object on the heap for further manipulation
Map* startMapMaking() {
  int width = 0;
  int length = 0;
  cout << "Welcome to DnD Map Maker, adventurer!" << endl;

  getSizeInput(width, "width");
  getSizeInput(length, "length");
  Map* m = new Map(width, length);

  // Initially display map and instructions
  cout << endl;
  cout << "This is a vast wasteland (empty map)." << endl;
  m->displayMap();
  cout << "The 'origin' of the map is in the top left corner at (0,0)." << endl;
  cout << "This maps allows placement of walls (W), start doors (S), end doors (E). characters (C), treasure chests (T) and opponents (O)." << endl;
  cout << "Valid maps are ones with a closed wall, at least two doors attached, and a clear path between these doors." << endl;
  cout << "As an example, by entering the string 'W12', you place a wall at 1 position to the *RIGHT* and 2 positions *DOWN*." << endl;
  cout << "The program *will not respond* if your input is not properly formatted." << endl;
  cout << "You can also enter 'reset' to start over again, 'validate' to check the map for errors or 'quit' to exit the program. Have fun!" << endl;
  cout << endl;
  return m;
}


//! main() function. Entry point of the program.
//! It parses the passed arguments and either does the following:
//! - Runs the test suite:
//!   1. Create a test suite object from the registry as populated by the code in the Test Classes
//!   2. Create a test runner that will execute all the tests in the registry
//!   3. (optionally) sets an outputter that will output the results
//!   4. Run the test cases.
//! - Runs the main map creation program:
//!   1. Initializes a map based on user input.
//!   2. Assumption that the smallest possible map grid is of size 2x2.
//!   3. Provides instructions to the user as to how the program works.
//!   4. Continually parse user input and execute valid operations.

int main(int argc, char* argv[]) {

  // Checking if test command-lind parameter was passed.
  if (argc > 1) {
    string testString(argv[1]);
    if (testString.compare("test") == 0) {
      // Run test suite

      // Get the top level suite from the registry
      CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

      // Adds the test to the list of test to run
      CppUnit::TextUi::TestRunner runner;
      runner.addTest( suite );

      // Change the default outputter to a compiler error format outputter
      runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                           std::cerr ) );
      // Run the tests.
      bool wasSucessful = runner.run();

      getchar();

      // Return error code 1 if the one of test failed.
      return wasSucessful ? 0 : 1;
    }
  } else {
    // Run main program

    // Initalize map and provide instructions
    Map* m = startMapMaking();

    // Game Loop
    string input;
    while (true) {
      // Get user input and analyze response for valid choices
      cout << "$ ";
      getline(cin, input);

      if (input.compare("quit") == 0) {
        // delete heap-allocated memory and fix dangling pointer, then quit.
        delete m;
        m = NULL;
        cout << "Farewell, mere mortal." << endl;
        exit(0);
        continue;
      }

      if (input.compare("reset") == 0) {
        cout << "Resetting map making session..." << endl;
        startMapMaking();
      }
      if (input.compare("validate") == 0) {
        cout << "Checking map validity..." << endl;
        m->validatePath();
      }

      if (input.length() == 3 && input.find_first_of("WSECTO ") == 0) {
        int xpos = input.at(1) - '0';
        int ypos = input.at(2) - '0';
        if (xpos >= 0 && ypos >= 0 && xpos < m->getMapWidth() && ypos < m->getMapLength()) {
          m->fillCell(ypos, xpos, input.at(0));
          m->displayMap();
        }
      }
    }
    return 0;
  }
}
