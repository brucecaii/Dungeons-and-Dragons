#include "Subject.h"
#include "Observer.h"

Subject::Subject() { //! default construtor intilize your list that will store all your observers
	_observers = new list<Observer*>;
}
Subject::~Subject() {  //! destructor
	delete _observers;
}
void Subject::Attach(Observer* o) { //! adding an observer to your list of observers
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) { //! removing an observer from your list of observers
	_observers->remove(o);
};
void Subject::Notify() {  //! notifying all observers that a state change has occured in our subject
	list<Observer *>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)
		(*i)->Update();
};