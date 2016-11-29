#include <iostream>
#include "AggressorStrategy.h"
#include "Character.h"
#include "Map.h"

using std::cout;
using std::endl;


void AggressorStrategy::execute(Map& m, Character& c) {
  this->moveCloserToHuman(m, c);
}
void AggressorStrategy::moveCloserToHuman(Map& m, Character& c) {
  int charPosX = c.getCurrentPositionX();
  int charPosY = c.getCurrentPositionY();
  int humanPosX = m.getHumanPosition()[0];
  int humanPosY = m.getHumanPosition()[0];
  int originalDistance = this->shortestDistanceToHuman(charPosX, charPosY, humanPosX, humanPosY);

  cout << "charPosX =" << c.getCurrentPositionX() << endl;
  cout << "charPosY =" << c.getCurrentPositionY() << endl;
  cout << "originalDistance" << originalDistance<< endl;

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

int AggressorStrategy::shortestDistanceToHuman(int charPosX, int charPosY, int humanPosX, int humanPosY) {
    return abs(charPosX-humanPosX) + abs(charPosY-humanPosY);
}



void AggressorStrategy::moveUp(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

void AggressorStrategy::moveDown(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

void AggressorStrategy::moveLeft(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(int(currentPosition[1]));
}

void AggressorStrategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(currentPosition[1]);
}




