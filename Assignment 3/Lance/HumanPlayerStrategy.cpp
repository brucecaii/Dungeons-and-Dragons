#include <iostream>
#include <string>
#include <ctype.h>

#include "Character.h"
#include "HumanPlayerStrategy.h"
#include "Map.h"

using std::cin;
using std::cout;
using std::endl;



void HumanPlayerStrategy::execute(Map& m, Character& c) {
  m.display();
  this->movePlayer(m,c);
}

void HumanPlayerStrategy::movePlayer(Map& m, Character& c) {
  int charPosX = c.getCurrentPositionX();
  int charPosY = c.getCurrentPositionY();

  string temp;
  cout << "MOVE: Enter 'w' for up, 'a' for left, 's' for down or 'd' for right." << endl;
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
//void Character::openChest(Map m) {
  ////If the character is beside a chest
  //if (m.isBeside(currentPosition[0], currentPosition[1], 'T') == 1) {
    //cout << "Opening chest... Surprise!" << endl;
  //} else {
    //cout << "There is no chest around you. Nothing to open." << endl;
  //}
//}
//


void HumanPlayerStrategy::moveUp(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

void HumanPlayerStrategy::moveDown(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[0]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionX(currentPosition[0]);
}

void HumanPlayerStrategy::moveLeft(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]--;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(int(currentPosition[1]));
}

void HumanPlayerStrategy::moveRight(Map& m, Character& c) {
  vector<int> currentPosition = {c.getCurrentPositionX(), c.getCurrentPositionY()};
  vector<int> humanPosition = {m.getHumanPosition()[0], m.getHumanPosition()[1]};
  m.clearCell(currentPosition[0], currentPosition[1]);
  currentPosition[1]++;
  m.setCell(currentPosition[0], currentPosition[1], c.getTypeOnMap());
  c.setCurrentPositionY(currentPosition[1]);
}
