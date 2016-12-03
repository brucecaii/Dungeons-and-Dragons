#include "CharacterObserver.h"

CharacterObserver::CharacterObserver()
{
}

CharacterObserver::CharacterObserver(Character * c)
{
	_subject = c;
	_subject->Attach(this);
}

CharacterObserver::~CharacterObserver()
{
	_subject->Detach(this);
}

void CharacterObserver::Update()
{
	display();
}

void CharacterObserver::UpdateLog(string className, string methodName, string message)
{
}

void CharacterObserver::display()
{
	this->_subject->displayCharacterInfo();
	//this->_subject->displayCharacterEquipment();
	//this->_subject->displayCharacterBackpack();
}

void CharacterObserver::toggleLogger(bool trigger)
{
	this->_isActive = trigger;
}

void CharacterObserver::turnOn()
{
	this->toggleLogger(true);
}

void CharacterObserver::turnOff()
{
	this->toggleLogger(true);
}
