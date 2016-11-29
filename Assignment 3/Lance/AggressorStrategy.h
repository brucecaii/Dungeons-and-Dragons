#pragma once

#include "Character.h"
#include "Map.h"

class AggressorStrategy : public Strategy {
  using Strategy::execute;
  using Strategy::moveUp;
  using Strategy::moveDown;
  using Strategy::moveLeft;
  using Strategy::moveRight;
  public:
    void execute(Map& m, Character& character);
    void moveCloserToHuman(Map& m, Character& character);
    void moveUp(Map& m, Character& character);
    void moveDown(Map& m, Character& character);
    void moveLeft(Map& m, Character& character);
    void moveRight(Map& m, Character& character);
    int shortestDistanceToHuman(int charPosX, int charPosY, int humanPosX, int humanPosY);
};

