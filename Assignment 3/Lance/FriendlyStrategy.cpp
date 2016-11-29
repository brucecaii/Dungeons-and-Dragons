//! @file
//! @brief Implementation file for the FriendlyStrategy class
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
#include <stdlib.h>
#include "Character.h"
#include "FriendlyStrategy.h"
#include "Map.h"

using std::cout;
using std::endl;

//! Implementation of the Strategy pattern execute method. In this case, if the character is alive, they are displaced by 1 cell towards the human player.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::execute(Map& m, Character& c) {
  if (c.getHitPoints() > 0) {
    c.displayCharacter();
    this->moveCloserToHuman(m, c);
  }
}

//! Implementation of the moveCloserToHuman method. This method evaluates the character's current position and its distance from the human player.  Once the proper direction is established, the character is moved one tile in the general direction of the human player.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::moveCloserToHuman(Map& m, Character& c) {
  int charPosX = c.getCurrentPositionX();
  int charPosY = c.getCurrentPositionY();
  int humanPosX = m.getHumanPosition()[0];
  int humanPosY = m.getHumanPosition()[0];
  int originalDistance = this->shortestDistanceToHuman(charPosX, charPosY, humanPosX, humanPosY);

  if (originalDistance != 0) {
    if (charPosX>0 &&
        m.getCell(charPosX-1, charPosY) == ' ' &&
        this->shortestDistanceToHuman(charPosX-1, charPosY, humanPosX, humanPosY) <= originalDistance) {
      this->moveUp(m,c);
    } else if (charPosY>0 &&
        m.getCell(charPosX, charPosY-1) == ' ' &&
        this->shortestDistanceToHuman(charPosX, charPosY-1, humanPosX, humanPosY) <= originalDistance) {
      this->moveLeft(m,c);
    } else if (charPosX<m.getMapWidth()-1 &&
        m.getCell(charPosX+1, charPosY) == ' ' &&
        this->shortestDistanceToHuman(charPosX+1, charPosY, humanPosX, humanPosY) <= originalDistance) {
      this->moveDown(m,c);
    } else if (charPosY<m.getMapLength()-1 &&
        m.getCell(charPosX, charPosY+1) == ' ' &&
        this->shortestDistanceToHuman(charPosX, charPosY+1, humanPosX, humanPosY) <= originalDistance) {
      this->moveRight(m,c);
    }
  }
}

//! Implementation of the shortestDistanceToHuman method. This method is the measure for how far away a human player is. Is it used in established the direction in which the human player is.
//! IMPORTANT TO DO FOR FINAL DELIVERABLE:
//! - Better path finding algorithm (eg. shortestDistanceToHuman method). Currently, the algorithm used does not consider obstacles such as walls, other characters, etc.
//! @param int for current character's x-coordinate
//! @param int for current character's y-coordinate
//! @param int for human player's x-coordinate
//! @param int for human player's y-coordinate
int FriendlyStrategy::shortestDistanceToHuman(int charPosX, int charPosY, int humanPosX, int humanPosY) {
    return abs(charPosX-humanPosX) + abs(charPosY-humanPosY);
}

//! Implementation of the moveUp method. This changes the character's position state and the map's representation one cell upwards
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::moveUp(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

//! Implementation of the moveDown method. This changes the character's position state and the map's representation one cell downwards.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::moveDown(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

//! Implementation of the moveLeft method. This changes the character's position state and the map's representation one cell to the left.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::moveLeft(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(int(currentPosition[1]));
}

//! Implementation of the moveRight method. This changes the character's position state and the map's representation one cell to the right.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void FriendlyStrategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(currentPosition[1]);
}
