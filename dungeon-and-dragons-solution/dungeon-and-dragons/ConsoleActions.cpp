#include "ConsoleActions.h"

void ConsoleActions::initializeCharacterViews() {
	for (int i = 0; i < GameData::availableCharacters.size(); i++)
	{
		CharacterObserver* tempObs = new CharacterObserver(GameData::availableCharacters[i]);
	}
}

void ConsoleActions::consoleGameplayOptions() {
	int option;
	cout << "===============================" << endl;
	cout << "Character Menu" << endl;
	cout << "===============================" << endl;
	cout << "(1) Inventory View      (2) Toggle Character View" << endl;
	cout << "Please enter your choice: " << endl;
	cin >> option;

	if (option == 1) {
		triggerInventoryView();
	}
	else if (option == 2) {
		triggerCharacterView();
	}
}

void ConsoleActions::triggerInventoryView() {
	int choice;
	int inventoryIndex;
	string itemType;

	cout << "===============================" << endl;
	cout << "Character Inventory View" << endl;
	cout << "===============================" << endl;
	GameData::currentCharacterObject->displayCharacterEquipment();
	GameData::currentCharacterObject->displayCharacterBackpack();
	cout << endl;

	cout << "Please pick one of the following options: " << endl;
	cout << "(1) Equip Item      (2) Unequip Item      (3) Back" << endl;

	cin >> choice;

	if (choice < 3)
	{
		cout << "Not a valid option!" << endl;
	}

	if (choice == 1) {
		cout << "Please enter the item index you want to equip your character with: " << endl;
		cin >> inventoryIndex;

		//If index is out of bound
		if (inventoryIndex > GameData::currentCharacterObject->getCharacterBackpack()->getItems().size())
		{
			cout << "Not a valid entry." << endl;
			return;
		}

		auto items = GameData::currentCharacterObject->getCharacterBackpack()->getItems();

		//Equipping character with respective inventory index
		GameData::currentCharacterObject->equipItem(items[inventoryIndex]);

		//Re-display after the action
		GameData::currentCharacterObject->displayCharacterEquipment();
		GameData::currentCharacterObject->displayCharacterBackpack();

		cout << "===============================" << endl;
	}
	else if (choice == 2) {
		cout << "Please enter the item type you want to unequip from your character: " << endl;
		cin >> itemType;

		//DeEquipping character with respective item type
		GameData::currentCharacterObject->deEquipItem(itemType);

		//Re-display after the action
		GameData::currentCharacterObject->displayCharacterEquipment();
		GameData::currentCharacterObject->displayCharacterBackpack();

		cout << "===============================" << endl;
		//When done, go back to main menu
	}
	else if (choice == 3) {
		//Go back to main menu
		consoleGameplayOptions();
	}

}

void ConsoleActions::triggerCharacterView() {

	int choice;

	cout << "===============================" << endl;
	cout << "Triggering Character Views" << endl;
	cout << "===============================" << endl;

	for (int i = 0; i < GameData::availableCharacters.size(); i++)
	{
		cout << "[" + to_string(i) + "] " + GameData::availableCharacters[i]->getTypeInString()
			+ " [" + to_string(GameData::availableCharacters[i]->getTrigger()) + "]" << endl;
	}

	//Get input from user
	cout << "Enter View to Toggle On/Off (999 to go back to menu): " << endl;
	cin >> choice;
	cout << endl;

	if (choice != 999) {
		//Triggering on/off
		bool currentTrigger = (GameData::availableCharacters[choice]->getTrigger());

		if (currentTrigger == false) {
			GameData::availableCharacters[choice]->turnOnView();
			GameData::availableCharacters[choice]->displayCharacterInfo();
			cout << GameData::availableCharacters[choice]->getTypeInString() + " view turned on." << endl;
		}
		else {
			GameData::availableCharacters[choice]->turnOffView();
			cout << GameData::availableCharacters[choice]->getTypeInString() + " view turned off." << endl;
		}
	}

	cout << "===============================" << endl;

	//When done, call back main menu
	consoleGameplayOptions();
}

void ConsoleActions::TogglingLogger(){
	
	int choice;
	cout << "===============================" << endl;
	cout << "Toggle Game Loggers" << endl;
	cout << "===============================" << endl;
	cout << "[1] Event Controller Logger [" + to_string(GameData::eventLogger->getToggleValue()) + "]" << endl;
	cout << "[2] Map Controller Logger [" + to_string(GameData::mapLogger->getToggleValue()) + "]" << endl;
	cout << "[3] Character Controller Logger [" + to_string(GameData::characterLogger->getToggleValue()) + "]" << endl;
	cout << "[4] Dice Controller Logger [" + to_string(GameData::diceLogger->getToggleValue()) + "]" << endl;
	cout << "Please pick which logger you want to turn on/off: ";
	cin >> choice;
	
	if (choice == 1)
	{
		if (GameData::eventLogger->getToggleValue() == true){
			GameData::eventLogger->turnOff();
			cout << "Event Controller Logger has been turned off." << endl;
		}
		else {
			GameData::eventLogger->turnOn();
			cout << "Event Controller Logger has been turned on." << endl;
		}
	}

	if (choice == 2)
	{
		if (GameData::mapLogger->getToggleValue() == true) {
			GameData::mapLogger->turnOff();
			cout << "Map Logger has been turned off." << endl;
		}
		else {
			GameData::mapLogger->turnOn();
			cout << "Map Logger has been turned on." << endl;
		}
	}

	if (choice == 3)
	{
		if (GameData::characterLogger->getToggleValue() == true) {
			GameData::characterLogger->turnOff();
			cout << "Character Logger has been turned off." << endl;
		}
		else {
			GameData::characterLogger->turnOn();
			cout << "Character Logger has been turned on." << endl;
		}
	}

	if (choice == 4)
	{
		if (GameData::diceLogger->getToggleValue() == true) {
			GameData::diceLogger->turnOff();
			cout << "Dice Logger has been turned off." << endl;
		}
		else {
			GameData::diceLogger->turnOn();
			cout << "Dice Logger has been turned on." << endl;
		}
	}

	cout << "===============================" << endl;
	TogglingLogger();
}