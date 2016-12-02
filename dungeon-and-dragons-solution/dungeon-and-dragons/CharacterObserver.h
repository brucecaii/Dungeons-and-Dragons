#pragma once
#include "Observer.h"
#include "Character/Character.h"

class CharacterObserver : public Observer {

public:
	CharacterObserver();
	CharacterObserver(Character* c);
	~CharacterObserver();
	void Update();
	void UpdateLog();
	void display();

private:
	Character *_subject;
};