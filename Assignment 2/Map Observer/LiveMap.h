#pragma once
#include "Observer.h"
#include "Map.h"

class LiveMap : public Observer {
	
	public:
		LiveMap();
		LiveMap(Map* m);
		~LiveMap();
		void Update();
		void display();

	private:
		Map *_subject;
};