#include "Dice.h"

Dice::Dice()
{
}

Dice::~Dice()
{
}

vector<int> Dice::roll(string dice) {
	//! validate input and return -1 on invalid string input 
	const regex diceStr("^([1-9]+[0-9]*d(4|6|8|100|10|12|20)){1}([+][1-9]+[0-9]*)*$");
	vector<int> empty;
	if (!regex_match(dice, diceStr)) return empty;
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
	vector<int> result;
	for (int j = 0; j < roll; j++) {
		//! TODO: Implement a better algorithm for rolling random number
		//! This currently generate completely random number but specific to one time per sec. (time relative)
		int random = rand() % range + 1;
		result.push_back(random);
	}
	result.push_back(opt);

	//Getting string of result
	string resultString = "[";
	for (int i = 0; i < result.size(); i++) {
		if (i == result.size() - 1) {
			resultString += to_string(result[i]) + "]";
		} else {
			resultString += to_string(result[i]) + ", ";
		}
	}

	UpdateLog("Dice", "roll", "Dice was rolled with " + dice + ", results obtained are: " + resultString);
	return result;
}


