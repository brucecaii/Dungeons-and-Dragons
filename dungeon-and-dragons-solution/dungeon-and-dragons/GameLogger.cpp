#include "GameLogger.h"
#include <ctime>
#include <iostream>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::fstream;

using namespace std;

//! default constructor
GameLogger::GameLogger() {
};

//! Parameterized Constructor of GameLogger (observer) that attaches to a character (subject)
//! @param c: a character pointer in which GameLogger will attach itself to 
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(Character* c, bool isLogging)
{
	_characterSubject = c;
	_characterSubject->Attach(this);
	_isActive = isLogging;
};

//! Parameterized constructor of GamerLogger (observer) that attaches to a ItemFileIO (subject)
//! @param itfio: a ItemFileIO pointer in which GameLogger will attach itself to 
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(ItemFileIO* itfio, bool isLogging)
{
	_itemIOSubject = itfio;
	_itemIOSubject->Attach(this);
	_isActive = isLogging;
};

//! Parameterized constructor of GameLogger (observer) that attaches to a CharacterFileIO (subject)
//! @param cfio: a CharacterFileIO pointer in which GameLogger will attach itself to 
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(CharacterFileIO* cfio, bool isLogging)
{
	_charIOSubject = cfio;
	_charIOSubject->Attach(this);
	_isActive = isLogging;
};

//! Parameterized constructor of GameLogger (observer) that attaches to a Map (subject)
//! @param map: a map pointer in which GameLogger will attach itself to 
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(Map* map, bool isLogging)
{
	_mapSubject = map;
	_mapSubject->Attach(this);
	_isActive = isLogging;
};

//! Parameterized constructor of GameLogger (observer) that attaches to a Dice (subject)
//! @param dice: a dice pointer in which GameLogger will attach itself to
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(Dice* dice, bool isLogging)
{
	_diceSubject = dice;
	_diceSubject->Attach(this);
	_isActive = isLogging;
}

//! Parameterized constructor of GameLogger (observer) that attaches to a CharacterBuilder (subject)
//! @param cb: a CharacterBuilder pointer in which GameLogger will attach itself to
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(CharacterBuilder * cb, bool isLogging)
{
	_charBuilder = cb;
	_charBuilder->Attach(this);
	_isActive = isLogging;
}

//! Parameterized constructor of GameLogger (observer) that attaches to a CharacterBuilder (subject)
//! @param cb: a CharacterBuilder pointer in which GameLogger will attach itself to
//! @param isLogging: a boolean to trigger logging on or off
GameLogger::GameLogger(CharacterStrategy * cs, bool isLogging)
{
	_charStrategy = cs;
	_charStrategy->Attach(this);
	_isActive = isLogging;
}
;

//! Deconstructor of observer LiveMap 
GameLogger::~GameLogger()
{
	delete this;
};

void GameLogger::Update() {};

//! Method to update and trigger a display of the subject
void GameLogger::UpdateLog(string className, string methodName, string message)
{
	Display(className, methodName, message);
};

//! Method to display right information in logger
void GameLogger::Display(string className, string methodName, string message)
{
	if (this->_isActive)
	{
		// Using C++ 11 to create a time object with the current time
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);

		// Formatting the time and converting it into a string
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		auto str = oss.str();

		// Building the origin ClassName::MethodName
		string origin = "FROM: " + className + "::" + methodName;

		// Building the complete log string
		string logMsg = "[" + str + "]" +
			"[" + origin + "] " + message + "\n";

		//Open the file and append
		ofstream file;
		file.open("GameLog.log", fstream::app);
		file << logMsg;
	}
}

void GameLogger::toggleLogger(bool trigger)
{
	this->_isActive = trigger;
}
