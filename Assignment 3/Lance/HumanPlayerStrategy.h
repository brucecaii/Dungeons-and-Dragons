#pragma once

#include "Character.h"
#include "Map.h"

class HumanPlayerStrategy : public Strategy {
  using Strategy::execute;
  public:
    void execute(Map& m, Character& c);
};

