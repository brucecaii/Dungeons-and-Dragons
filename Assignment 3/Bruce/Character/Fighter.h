#ifndef FIGHTER_H
#define FIGHTER_H

#include "Character.h"
#include "CharacterAttr.h"

class Fighter : public Character {

public:
	Fighter();
	Fighter(CharacterAttr *characterAttr);
	virtual ~Fighter();
	void setPlayerType(string playerType);
	string getPlayerType() const;

private:
	string playerType;
};

class Bully : public Fighter {

public: 
	Bully(CharacterAttr *characterAttr);
	~Bully();

};

class Nimble : public Fighter {

public:
	Nimble(CharacterAttr *characterAttr);
	~Nimble();

};

class Tank : public Fighter {

public:
	Tank(CharacterAttr *characterAttr);
	~Tank();

};

#endif 