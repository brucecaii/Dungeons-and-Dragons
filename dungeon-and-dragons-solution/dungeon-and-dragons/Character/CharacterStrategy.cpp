#include "CharacterStrategy.h"
#include "Character.h"
#include "../Map/Map.h"

//! Implementation of the moveUp method. This changes the character's position state and the map's representation one cell upwards
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void CharacterStrategy::moveLeft(Map& m, Character& c) {
  vector<int> currentPosition = c.getCurrentPosition();
  vector<int> humanPosition = m.getHumanPosition();
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPosition(currentPosition);
}

//! Implementation of the moveDown method. This changes the character's position state and the map's representation one cell downwards.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void CharacterStrategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = c.getCurrentPosition();
  vector<int> humanPosition = m.getHumanPosition();
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPosition(currentPosition);
}

//! Implementation of the moveLeft method. This changes the character's position state and the map's representation one cell to the left.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void CharacterStrategy::moveUp(Map& m, Character& c) {
  vector<int> currentPosition = c.getCurrentPosition();
  vector<int> humanPosition = m.getHumanPosition();
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPosition(currentPosition);
}

//! Implementation of the moveRight method. This changes the character's position state and the map's representation one cell to the right.
//! @param Reference to the map currently being played
//! @param Reference to the character that this strategy belongs to.
void CharacterStrategy::moveDown(Map& m, Character& c) {
  vector<int> currentPosition = c.getCurrentPosition();
  vector<int> humanPosition = m.getHumanPosition();
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPosition(currentPosition);
}


