#pragma once
#include <string>
using std::string;

class Observer {

public:
	~Observer();
	virtual void Update() = 0;
	virtual void UpdateLog(string className, string methodName, string message) = 0;

protected:
	Observer();
};