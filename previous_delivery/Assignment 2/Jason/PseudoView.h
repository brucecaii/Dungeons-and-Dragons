#pragma once

#pragma once
#include "Observer.h"
#include "Character.h"

class PseudoView : public Observer {
public:
	PseudoView();
	PseudoView(Character* s);
	PseudoView(Fighter* s);
	~PseudoView();
	void Update();
	void display();
private:
	Character *_subject;
};
