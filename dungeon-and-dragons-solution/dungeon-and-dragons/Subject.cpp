#include "Subject.h"
#include "Observer.h"

//! Default constructor of a subject
Subject::Subject() {
	_observers = new list<Observer*>;
}

//! Desconstructor of a subject
Subject::~Subject() {
	delete _observers;
}

//! Method to attach an observer to the subject
//! @param *o: a pointer to an observer
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};

//! Method to detach an observer from the subject
//! @param *o: a pointer to an observer
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};

//! Method to notify all observers when subject changes
void Subject::Notify() {
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
}

//! Method to notify observers that a change has been made and needs to log
void Subject::UpdateLog(string className, string methodName, string message)
{
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->UpdateLog(className, methodName, message);
};

