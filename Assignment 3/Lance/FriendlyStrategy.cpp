#include <iostream>
#include <stdlib.h>
#include "Character.h"
#include "FriendlyStrategy.h"
#include "Map.h"

using std::cout;
using std::endl;


void FriendlyStrategy::execute(Map& m, Character& c) {
  this->moveCloserToHuman(m, c);
}

void FriendlyStrategy::moveCloserToHuman(Map& m, Character& c) {
  int originalDistance = this->shortestDistanceToHuman(m,c);
  if (originalDistance == 0) {
    cout << "something broke: human and friendly should never be the same. Exiting" << endl;
  }
  cout << originalDistance << endl;

  // Try moving in all directions
  this->moveUp(m,c);
  if (this->shortestDistanceToHuman(m,c) < originalDistance)
    return;
  this->moveDown(m,c);

  this->moveDown(m,c);
  if (this->shortestDistanceToHuman(m,c) < originalDistance)
    return;
  this->moveUp(m,c);

  this->moveRight(m,c);
  if (this->shortestDistanceToHuman(m,c) < originalDistance)
    return;
  this->moveLeft(m,c);

  this->moveLeft(m,c);
  if (this->shortestDistanceToHuman(m,c) < originalDistance)
    return;
  this->moveRight(m,c);

  // FIX SET CHARACTER
}

int FriendlyStrategy::shortestDistanceToHuman(Map& m, Character& c) {
  // Pathfinding algorithm needs to be adapted to avoid obstacles
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  if (m.getCell(currentPosition[0], currentPosition[1]) == 'S'){
    return 0;
  }
  return abs(currentPosition[0]-humanPosition[0]) + abs(currentPosition[1]-humanPosition[1]);
}



void FriendlyStrategy::moveUp(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  if (currentPosition[1] == 0) {
    cout << "Cannot move further, please select a different direction." << endl;
  } else {
    if (
        m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'W' ||
        m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'T' ||
        m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'C' ||
        m.getCell(currentPosition[0], currentPosition[1]-1 ) == 'O'
        ) {
      cout << "You cannot move into a wall, treasure, or character; please pick a different direction." << endl;
    } else {
      m.clearCell(currentPosition[0], currentPosition[1]);
      currentPosition[1]--;
      m.setCharacter(currentPosition[0], currentPosition[1]);
    }
  }
}

void FriendlyStrategy::moveDown(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  if (currentPosition[1] == (m.getMapWidth()-1)) {
    cout << "Cannot move further, please select a different direction." << endl;
  } else {
    if (
        m.getCell(currentPosition[0], currentPosition[1] + 1) == 'W' ||
        m.getCell(currentPosition[0], currentPosition[1] + 1) == 'T' ||
        m.getCell(currentPosition[0], currentPosition[1] + 1) == 'C' ||
        m.getCell(currentPosition[0], currentPosition[1] + 1) == 'O'
        ) {
      cout << "You cannot move into a wall, treasure, or character; please pick a different direction." << endl;
    }else{
      m.clearCell(currentPosition[0], currentPosition[1]);
      currentPosition[1]++;
      m.setCharacter(currentPosition[0], currentPosition[1]);
    }
  }
}

void FriendlyStrategy::moveLeft(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  if (currentPosition[0] == 0) {
    cout << "Cannot move further, please select a different direction." << endl;
  } else {
    if (
        m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'W' ||
        m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'T' ||
        m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'C' ||
        m.getCell(currentPosition[0] - 1, currentPosition[1]) == 'O'
        ) {
      cout << "Cannot move into a wall, please select a different direction." << endl;
    } else {
      m.clearCell(currentPosition[0], currentPosition[1]);
      currentPosition[0]--;
      m.setCharacter(currentPosition[0], currentPosition[1]);
    }
  }
}

void FriendlyStrategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  if (currentPosition[0] == (m.getMapLength()-1)) {
    cout << "Cannot move further, please select a different direction." << endl;
  } else {
    if (
        m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'W' ||
        m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'T' ||
        m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'C' ||
        m.getCell(currentPosition[0] + 1, currentPosition[1]) == 'O'
        ) {
      cout << "Cannot move into a wall, please select a different direction." << endl;
    } else {
      m.clearCell(currentPosition[0], currentPosition[1]);
      currentPosition[0]++;
      m.setCharacter(currentPosition[0], currentPosition[1]);
    }
  }
}



