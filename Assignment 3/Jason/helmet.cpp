#include "helmet.h"

helmet::helmet(Char * c) : Item(c)
{

	Enhancement *enhancement = new Enhancement("str", 20);
	vector<Enhancement> influence;
	influence.push_back(*enhancement);
	Item test1("Helmet", influence, "Concordia Hat");
	c->equipItem(test1);




}
