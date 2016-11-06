#include "PseudoView.h"
#include "Character.h"
#include <iostream>
using namespace std;

PseudoView::PseudoView() {
};
PseudoView::PseudoView(Character* s) {
	//! Upon instantiation, attaches itself to a Character
	_subject = s;
	
	_subject->Attach(this);
};
PseudoView::PseudoView(Fighter* s) {
	//! Upon instantiation, attaches itself to a Character
	_subject = s;
	
	_subject->Attach(this);
};

PseudoView::~PseudoView() {
	//! Upon destruction, detaches itself from its Character     
	_subject->Detach(this);
};
void PseudoView::Update() {
	display();
};
void PseudoView::display() { //! this is what is being displayed for this observer

	int hp = _subject->getHitPoints(); //! getting the hp from the class you are observering
	int strengh = _subject->getStrength();
	cout << "pseudo view class displaying new  hp is -->" << hp << endl;
	cout << " pseduo veiew class displaying strenght  : " << strengh << endl;
};
