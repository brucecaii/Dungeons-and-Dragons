//! Implement character (friendly or unfriendly) actions as strategy pattern
//! Each turn, a character can proceed with:
//! - move
//! - attack
//! - free action
//!
//! Must implement these ConcreteStrategies:
//! 1) a HumanPlayerStrategy that lets the user decide where to move, who to attack, and what free actions to take;
//! 2) an AggressorStrategy that make the character automatically move towards and attack the player character;
//! 3) a FriendlyStrategy that makes the character automatically move towards the character, but not attack unless attacked, in which case it adopts the AggressorStrategy.klA
//!
//! Strategy is the abstract class that all above ConcreteClasses extend from.
//
#pragma once
#include "../Map/Map.h"

class Character; // This forward declaration is needed. _DONT_TOUCH_IT_! (Lance)

class CharacterStrategy : public Subject {
  public:
    virtual void execute(Map& m, Character& character) = 0;
    void moveUp(Map& m, Character& character);
    void moveDown(Map& m, Character& character);
    void moveRight(Map& m, Character& character);
    void moveLeft(Map& m, Character& character);
};

