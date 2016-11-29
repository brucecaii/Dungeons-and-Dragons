#include "Map.h"
#include "LiveMap.h"

using namespace std;

LiveMap::LiveMap() {
};

LiveMap::LiveMap(Map* m)
{
	_subject = m;
	_subject->Attach(this);
};

LiveMap::~LiveMap()
{
	_subject->Detach(this);
};

void LiveMap::Update()
{
	display();
};

void LiveMap::display()
{
	this->_subject->displayMap();
}