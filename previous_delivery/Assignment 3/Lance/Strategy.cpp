#include "Strategy.h"
#include "Character.h"
#include "Map.h"

//! Implementation of the moveUp method. This changes the character's position state and the map's representation one cell upwards
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void Strategy::moveUp(Map& m, Character& c) {
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
void Strategy::moveDown(Map& m, Character& c) {
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
void Strategy::moveLeft(Map& m, Character& c) {
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
void Strategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(currentPosition[1]);
}

