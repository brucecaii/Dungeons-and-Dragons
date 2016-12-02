//! @file
//! @brief Implementation file for the HumanPlayerStrategy class
//!
//! Implement character (friendly or unfriendly) actions as strategy pattern
//! Each turn, a character can proceed with:
//! - move
//! - attack
//! - free action
//!
//! Must implement these ConcreteStrategies:
//! 1) a HumanPlayerStrategy that lets the user decide where to move, who to attack, and what free actions to take;
//! 2) an AggressorStrategy that make the character automatically move towards and attack the player character;
//! 3) a FriendlyStrategy that makes the character automatically move towards the character, but not attack unless attacked, in which case it adopts the AggressorStrategy.klA

#include <iostream>
#include <string>
#include <ctype.h>

#include "Character.h"
#include "HumanPlayerStrategy.h"
#include "Map.h"
#include "Global.h"
#include "AggressorStrategy.h"

using std::cin;
using std::cout;
using std::endl;

//! Implementation of the Strategy pattern execute method. In this case, if the character is alive, the map and character information is displayed. The player is moved based on user feedback, and if there is an adjacent character available to attack, the user can chose to decide to attack or not.
//! If the user is dead/unconscious, the game ends.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void HumanPlayerStrategy::execute(Map& m, Character& c) {
  if (c.getHitPoints() > 0) {
    c.displayCharacter();
    m.display();
    this->movePlayer(m,c);
    m.display();
    this->canAttackOneAdjacentCharacter(m, c);
  } else {
    cout << endl;
    cout << "*****************************" << endl;
    cout << "* You have died! Game over! *" << endl;
    cout << "*****************************" << endl;
    cout << endl;
    exit(0);
  }
}

//! Implementation of the movePlayer character. In response to user feedback, the character is moved to an empty map cell adjacent to the human player character.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void HumanPlayerStrategy::movePlayer(Map& m, Character& c) {
  int charPosX = c.getCurrentPositionX();
  int charPosY = c.getCurrentPositionY();

  string temp;
  cout << "MOVE: Enter [w] for up, [a] for left, [s] for down or [d] for right." << endl;
  getline(cin, temp);


  if (temp.size()>0) {
    if (tolower(temp.at(0)) == 'w' &&
        charPosX>0 &&
        (m.getCell(charPosX-1, charPosY) == ' ' || m.getCell(charPosX-1, charPosY) == 'E')) {
      this->moveUp(m,c);
    } else if (tolower(temp.at(0)) == 'a' &&
        charPosY>0 &&
        (m.getCell(charPosX, charPosY-1) == ' ' || m.getCell(charPosX, charPosY-1) == 'E')) {
      this->moveLeft(m,c);
    } else if (tolower(temp.at(0)) == 's' &&
        charPosX<m.getMapWidth()-1 &&
        (m.getCell(charPosX+1, charPosY) == ' ' || m.getCell(charPosX+1, charPosY) == 'E')) {
      this->moveDown(m,c);
    } else if (tolower(temp.at(0)) == 'd' &&
        charPosY<m.getMapLength()-1 &&
        (m.getCell(charPosX, charPosY+1) == ' ' || m.getCell(charPosX, charPosY+1) == 'E')) {
      this->moveRight(m,c);
    }
  }
}
//! Implementation of the canAttackOneAdjacentCharacter method. This checks all directions for adjacent cells occupied by a character. If a character is found, that character is attacked in response to the user's input.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void HumanPlayerStrategy::canAttackOneAdjacentCharacter(Map& m, Character& c) {
  int charPosX = c.getCurrentPositionX();
  int charPosY = c.getCurrentPositionY();
  if (charPosX>0 &&
      (m.getCell(charPosX-1, charPosY) == 'C' ||
       m.getCell(charPosX-1, charPosY) == 'O')) {
    string answer;
    cout << "ATTACK: Do you want to attack the character above you? Enter [y] or [n]." << endl;
    getline(cin, answer);
    if (answer.size()>0 && tolower(answer.at(0)) == 'y') {
      this->attackCharacterAtPosition(c,charPosX-1, charPosY);
    }
  } else if (charPosY>0 &&
      (m.getCell(charPosX, charPosY-1) == 'C' ||
       m.getCell(charPosX, charPosY-1) == 'O')) {
    string answer;
    cout << "ATTACK: Do you want to attack the character to your left? Enter [y] or [n]." << endl;
    getline(cin, answer);
    if (answer.size()>0 && tolower(answer.at(0)) == 'y') {
      this->attackCharacterAtPosition(c,charPosX, charPosY-1);
    }
  } else if (charPosX<m.getMapWidth()-1 &&
      (m.getCell(charPosX+1, charPosY) == 'C' ||
       m.getCell(charPosX+1, charPosY) == 'O')) {
    string answer;
    cout << "ATTACK: Do you want to attack the character below you? Enter [y] or [n]." << endl;
    getline(cin, answer);
    if (answer.size()>0 && tolower(answer.at(0)) == 'y') {
      this->attackCharacterAtPosition(c,charPosX+1, charPosY);
    }
  } else if (charPosY<m.getMapLength()-1 &&
      (m.getCell(charPosX, charPosY+1) == 'C' ||
       m.getCell(charPosX, charPosY+1) == 'O')) {
    string answer;
    cout << "ATTACK: Do you want to attack the character to your right? Enter [y] or [n]." << endl;
    getline(cin, answer);
    if (answer.size()>0 && tolower(answer.at(0)) == 'y') {
      this->attackCharacterAtPosition(c,charPosX, charPosY+1);
    }
  }
}

//! Implementation of the attackCharacterAtPositionmethod. This checks a specific cell occupied by a character. If a character is found, that character is attacked.
//! @param Reference to the character that this strategy belongs to.
//! @param int for current character's x-coordinate
//! @param int for current character's y-coordinate
void HumanPlayerStrategy::attackCharacterAtPosition(Character& c, int charPosX, int charPosY) {
  //First need to find the character instance at position (charPosX, charPosY)
  Character* charBeingAttacked;
  for (int i = 0; i < (int)Global::gameCharacters.size(); i++) {
    if (Global::gameCharacters[i].getCurrentPositionX() == charPosX &&
        Global::gameCharacters[i].getCurrentPositionY() == charPosY) {
      charBeingAttacked = &Global::gameCharacters[i];
    }
  }

  // Now checking if character had the friendly strategy. If yes, it should now have the aggressor strategy.
  if (charBeingAttacked->getTypeOnMap() == 'C') {
    charBeingAttacked->setTypeOnMap('O');
    charBeingAttacked->setStrategy(new AggressorStrategy());
  }

  // Now remove hitpoints.
  // TO IMPLEMENT FOR FINAL DELIVERABLE:
  // - Proper multiple attack.
  // - proper attack success based on dice roll and armor class.
  // - proper hitpoints reduction if attack is successful.
  int tempHP = charBeingAttacked->getHitPoints();
  charBeingAttacked->setHitPoints(tempHP-1);
}
