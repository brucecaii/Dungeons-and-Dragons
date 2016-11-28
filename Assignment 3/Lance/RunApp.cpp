//! @file
//! @brief Driver file to drive the main program
//!
//!
//! Some assumptions about this program:
//! - The simplest possible case was chosen in order to satisfy all assignment requirements without additional complexity. Therefore, no items, item containers, or enhancements exist in the implementation of this game.
//! - No specific character classes were assumed.
//! - No other patterns (Observer, Builder) are illustrated in this assignment, since they are not strictly required and would add unneeded complexity to this simple showcasing of the Strategy pattern.
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!
//!

#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include "Map.h"
#include "Character.h"
#include "AggressorStrategy.h"
#include "FriendlyStrategy.h"
#include "HumanPlayerStrategy.h"

using std::cout;
using std::endl;
using std::get;
using std::ignore;
using std::tie;

int main(int argc, char* argv[]) {

  cout << "You are an adventurer 'S' on the map along with a friendly character 'C'." << endl;
  cout << "Watch out, if you attack other characters, they might get angry and become aggresive ('O')..." << endl;

  // Hardcoding a basic map
  Map m(5,5,"S                C       ");
  m.display();

  // Initializing all characters on the map
  vector<tuple<char,int,int>> characterPositions = m.getAllCharacterPositions();
  vector<Character> gameCharacters;

  for (int i = 0; i < (int)characterPositions.size(); i++) {
    // Create a new one with appropriate position and type
    char type; int posX; int posY;
    tie(type, posX, posY) = characterPositions[i];
    if (type == 'S') {
      cout << "There is a human character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new HumanPlayerStrategy(),posX,posY,type);
      gameCharacters.push_back(temp);
    }
    if (type == 'C') {
      cout << "There is a friendly character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new FriendlyStrategy(),posX,posY,type);
      gameCharacters.push_back(temp);
    }
    if (type == 'O') {
      cout << "There is an aggressor character at position ("<< posX << ","<< posY <<")" << endl;
      Character temp(6,6,6,6,6,6,new AggressorStrategy(),posX,posY,type);
      gameCharacters.push_back(temp);
    }
  }
  cout << endl;

  while (true) {
    for (Character character : gameCharacters) {
      character.executeStrategy(m);
    }
  }






  // Implement character (friendly or unfriendly) actions as strategy pattern
  // Each turn, a character can proceed with:
  // - move
  // - attack
  // - free action (only applicable one is dropping an item).
  //
  // Must implement these ConcreteStrategies:
  // 1) a HumanPlayerStrategy that lets the user decide where to move, who to attack, and what free actions to take;
  // 2) an AggressorStrategy that make the character automatically move towards and attack the player character;
  // 3) a FriendlyStrategy that makes the character automatically move towards the character, but not attack unless attacked, in which case it adopts the AggressorStrategy.klA
    return 0;
}
