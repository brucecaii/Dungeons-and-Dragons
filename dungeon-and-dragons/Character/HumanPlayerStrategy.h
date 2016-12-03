#pragma once

#include "Character.h"
#include "CharacterStrategy.h"
#include "../Map/Map.h"

class HumanPlayerStrategy : public CharacterStrategy {
  using CharacterStrategy::execute;
  public:
    void execute(Map& m, Character& c);
    void movePlayer(Map& m, Character& c);
    void canAttackOneAdjacentCharacter(Map& m, Character& c);
    void attackCharacterAtPosition(Character& c, int charPosX, int charPosY);
};

