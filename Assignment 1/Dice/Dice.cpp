//! @file 
//! @brief Implementation file for the Dice class  
//!
#include "Dice.h"

//! Implementation of the rolling dice
//! @param string : a string of the form "xdy[+z]".
//! @return an integer which is the addition of the value of all dice and return -1 when the expression dose not follow he right format 
//! TODO: structure the code into functions
int Dice::roll(string dice) {
	//! validate input and return -1 on invalid string input 
	const regex diceStr("^([1-9]+[0-9]*d(4|6|8|100|10|12|20)){1}([+][1-9]+[0-9]*)*$");
	if (!regex_match(dice, diceStr)) return -1;
	//! get dice time, dice type, and additional number
	int typeBreak, roll, range, opt;
	int optBreak = -1;
	int stringLength = dice.length();
	for (int i = 0; i < stringLength; i++) {
		if (dice[i] == 'd') typeBreak = i;
		if (dice[i] == '+') optBreak = i;
	}
	roll = stoi(dice.substr(0, typeBreak));
	if (optBreak == -1) {
		range = stoi(dice.substr(typeBreak + 1));
		opt = 0;
	}
	else {
		range = stoi(dice.substr(typeBreak + 1, optBreak - typeBreak - 1));
		opt = stoi(dice.substr(optBreak + 1));
	}
	//! compute result
	int result = 0;
	srand((int)time(NULL));
	for (int j = 0; j < roll; j++) {
		//! TODO: Implement a better algorithm for rolling random number
		//! This currently generate completely random number but specific to one time per sec. (time relative)
		int random = rand() % range + 1;
		result += random;
	}
	result += opt;
	return result;
}


