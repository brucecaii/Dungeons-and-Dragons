#pragma once
#ifndef FIGHTER_H
#define FIGHTER_H

#include "Character.h"
#include "CharacterAttr.h"

class Fighter : public Character {
public:
	Fighter();
	Fighter(CharacterAttr *characterAttr);
	virtual ~Fighter();
};

#endif 