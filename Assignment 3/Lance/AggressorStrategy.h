#pragma once

#include "Character.h"
#include "Map.h"

class AggressorStrategy : public Strategy {
  using Strategy::execute;
  public:
    void execute(Map& m, Character& character);
};

