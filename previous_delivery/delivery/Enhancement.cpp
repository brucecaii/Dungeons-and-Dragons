//! @file 
//! @brief Implementation file for the Item class  
//!
#include "Enhancement.h"

// default constructor

//! default constructor
Enhancement::Enhancement()
{
	type = "";
}

//! constructor that receives a type of item as a string and a bonus value as an int
//! @param type_name : type of the item
//! @param bonus_value : bonus given by the item [1..5]
Enhancement::Enhancement(string type_name, int bonus_value)
{
	type = type_name;
	bonus = bonus_value;
}

//! method to get the type of the item
//! @return : type of the item
string Enhancement::getType()
{
	return type;
}

//! method to get the bonus of the type
//! @return : bonus given by the item
int Enhancement::getBonus()
{
	return bonus;
}

//! method to validate the bous of the type
//! @return : true if it is legal according to rules (1-5), false if 
bool Enhancement::validateBonus()
{
	if (bonus > 5 || bonus < 1)
	{
		return false;
	}

	return true;
}


