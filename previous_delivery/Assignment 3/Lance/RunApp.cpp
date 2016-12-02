//! @file
//! @brief Driver file to drive the main program
//!
//! To run the program (Linux):
//! - Make sure you are in the project directory.
//! - $    g++ -g *.cpp -o test && ./test
//!
//! This program should also run easily on any platform.
//!
//! Doxygen HTML docs can be found in the html/ directory.
//!
//! Some assumptions about this program:
//! - The simplest possible case was chosen in order to satisfy all assignment requirements without additional complexity. Therefore, no items, item containers, or enhancements exist in the implementation of this game.
//! - No specific character classes were assumed.
//! - No other patterns (Observer, Builder) are illustrated in this assignment, since they are not strictly required and would add unneeded complexity to this simple showcasing of the Strategy pattern.
//!
//! Some future optimizations:
//! - Better path finding algorithm (eg. shortestDistanceToHuman method). Currently, the algorithm used does not consider obstacles such as walls, other characters, etc.
//! - Proper multiple attack.
//! - proper attack success based on dice roll and armor class.
//! - proper hitpoint reductions if attack is successful.

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "Map.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "HumanPlayerStrategy.h"
#include "Global.h"

using std::cout;
using std::endl;
using std::get;
using std::ignore;
using std::tie;


//! Program main method. Drives the creation of mock data (map and characters). Drives the program until the user's character dies or quits the game.
int main(int argc, char* argv[]) {

  cout << "You are an adventurer 'S' on the map along with a friendly character 'C'." << endl;
  cout << "Watch out, if you attack other characters, they might get angry and become aggresive ('O')..." << endl;

  // Hardcoding a basic map
  Map m(5,5,"S                C     O");
  m.display();

  // Initializing all characters on the map
  vector<tuple<char,int,int>> characterPositions = m.getAllCharacterPositions();

  for (int i = 0; i < (int)characterPositions.size(); i++) {
    // Create a new one with appropriate position and type
    char type; int posX; int posY;
    tie(type, posX, posY) = characterPositions[i];
    if (type == 'S') {
      cout << "There is a human character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new HumanPlayerStrategy(),posX,posY,type);
      Global::gameCharacters.push_back(temp);
    }
    if (type == 'C') {
      cout << "There is a friendly character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new FriendlyStrategy(),posX,posY,type);
      Global::gameCharacters.push_back(temp);
    }
    if (type == 'O') {
      cout << "There is an aggressor character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new AggressorStrategy(),posX,posY,type);
      Global::gameCharacters.push_back(temp);
    }
  }
  cout << endl;

  while (true) {
    for (int i = 0; i < (int)Global::gameCharacters.size(); i++) {
      Global::gameCharacters[i].executeStrategy(m);
    }
  }
  return 0;
}
