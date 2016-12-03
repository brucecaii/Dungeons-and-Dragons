#pragma once
#include "Observer.h"
#include "Character/Character.h"

class CharacterObserver : public Observer {

public:
	CharacterObserver();
	CharacterObserver(Character* c);
	~CharacterObserver();
	void Update();
	void UpdateLog(string className, string methodName, string message);
	void display();
	void toggleLogger(bool trigger);
	void turnOn();
	void turnOff();

private:
	Character *_subject;
	bool _isActive;
};