
#include <iostream>
#include "Map.h"
#include "LiveMap.h"
using namespace std;

int main(int argc, char* argv[])
{
	cout << "+=+=+=+=+Wecome to Dungeon and Jason+=+=+=+=+" << endl;

	//Create a Map to be observed
	Map *map = new Map(10, 10);

	//Create a live map that is connected to the Map
	LiveMap *liveMap = new LiveMap(map);

	map->displayMap();

	cout << endl; //Formatting purposes
	cout << endl;

	while (true)
	{
		//Get the user's input
		char userInput;
		cout << "Pick one of the followings:" << endl;
		cout << "w) Up \t s) Down \t a) Left \t d) Right" << endl;

		cin >> userInput;
	
		switch (userInput)
		{
			case('w'):
				map->moveUp();
				break;
			case('s'):
				map->moveDown();
				break;
			case('a'):
				map->moveLeft();
				break;
			case('d'):
				map->moveRight();
				break;
			default:
				cout << "Invalid input, please give an input between 1-4";
		}


	}

	

	int j; 
	std::cin >> j;

	// Return error code 1 if the one of test failed.
	//return wasSucessful ? 0 : 1;
	return 0;

}