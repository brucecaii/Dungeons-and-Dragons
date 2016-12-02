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

void CharacterObserver::UpdateLog()
{
}

void CharacterObserver::display()
{
	this->_subject->displayCharacterInfo();
	this->_subject->displayCharacterEquipment();
	this->_subject->displayCharacterBackpack();
}
