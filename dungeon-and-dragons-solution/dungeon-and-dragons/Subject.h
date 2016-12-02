#pragma once
#include "Observer.h"
#include <list>
#include <string>

using namespace std;

//! Needs to have a forward reference due to 
//! circular reference between Observer and Subject
class Observer;

class Subject {
public:
	virtual void Attach(Observer* o); //! observers will use this to add themselves to the list of observers
	virtual void Detach(Observer* o); //! like above but to remove
	virtual void Notify(); // ! this will notify all on observer list a state change of interest has occured
	virtual void UpdateLog(string className, string methodName, string message);
	virtual void toggleView(bool trigger);
	virtual void turnOnView();
	virtual void turnOffView();
	bool getTrigger();
	Subject();
	~Subject();
private:
	list<Observer*> *_observers;
	bool _isActive;
};
