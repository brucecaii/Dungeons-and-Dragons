#pragma once

#include "Character.h"
#include "Map.h"

class FriendlyStrategy : public Strategy {
  using Strategy::execute;
  public:
    void execute(Map& m, Character& c);
    void moveCloserToHuman(Map& m, Character &c);
    int shortestDistanceToHuman(Map& m, Character& c);
    void moveUp(Map& m, Character& c);
    void moveDown(Map& m, Character& c);
    void moveRight(Map& m, Character& c);
    void moveLeft(Map& m, Character& c);
};
