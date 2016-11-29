#pragma once

#include "Character.h"
#include "Strategy.h"
#include "Map.h"

class HumanPlayerStrategy : public Strategy {
  using Strategy::execute;
  using Strategy::moveUp;
  using Strategy::moveDown;
  using Strategy::moveLeft;
  using Strategy::moveRight;
  public:
    void execute(Map& m, Character& c);
    void movePlayer(Map& m, Character& c);
    void canAttackOneAdjacentCharacter(Map& m, Character& c);
    void attackCharacterAtPosition(Character& c, int charPosX, int charPosY);
};

