#include "Char.h"
#include "Item.h"






Char::Char()
{
}

Char::~Char()
{
}

void Char::equipItem(Item)
{

}

void Char::deEquipItem(string)
{
}

void Char::addItemBackpack(Item)
{
}

void Char::removeItemfromBackpack(string)
{
}

void Char::changeAttr(string type, int value, string action)
{
}

int Char::modifier(int dice, int bonus) const
{
	return 0;
}

void Char::levelUp()
{
}

bool Char::validateNewCharacter()
{
	return false;
}

int Char::getLevel() const
{
	return 0;
}

int Char::getHitPoint() const
{
	return 0;
}

void Char::setHitPoint(int hitPoint)
{
}

int Char::getArmorClass() const
{
	return 0;
}

void Char::setArmorClass(int armorClass)
{
}

vector<int> Char::getAttackBonus()
{
	return vector<int>();
}





void Char::setAttackBonus(const vector<int>& attackBonus)
{
}

ItemContainer * Char::getCharacterEquipment() const
{
	return nullptr;
}

void Char::setCharacterEquipment(ItemContainer * characterEquipment)
{
}

ItemContainer * Char::getCharacterBackpack() const
{
	return nullptr;
}

void Char::setCharacterBackpack(ItemContainer * characterBackpack)
{
}

CharacterAttr * Char::getCharacterAttr() const
{
	return nullptr;
}

void Char::setCharacterAttr(CharacterAttr * characterAttr)
{
}


