//! @file 
//! @brief Header file for the Dice class  
//!
#pragma once

#include <stdio.h>
#include <iostream>
#include <regex>
#include <random>
#include <ctime>
using namespace std;

//! class that implements the rolling of Dice 
class Dice {
	public:
		static int roll(string dice);
};

