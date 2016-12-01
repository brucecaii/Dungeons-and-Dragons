#include <string>
#include <chrono>
#include <thread>
#include "Character/CharacterGenerator.h"
#include "Map/Map.h"
#include "GameData.h"
#include "Character/AggressorStrategy.h"
#include "Character/FriendlyStrategy.h"
#include "Character/HumanPlayerStrategy.h"
#include "GUI/Gui.h"

#include <iostream>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

//! main() function. Entry point of the program.
//! Runs the main map creation program:
int main(int argc, char* argv[]) {

	//Items for testing purpose
	
	//Creating all the types of enhancements
	Enhancement intelligence("Intelligence", 5);
	Enhancement wisdom("Wisdom", 5);
	Enhancement armor("Armor class", 5);
	Enhancement strength("Strength", 5);
	Enhancement constitution("Constitution", 5);
	Enhancement charisma("Charisma", 5);
	Enhancement dexterity("Dexterity", 5);
	Enhancement attack("Attack bonus", 5);
	Enhancement damage("Damage bonus", 5);
	Enhancement fake("Fake Enhancement", 5);

	//Adding helmet allowed enhancements to vector
	vector<Enhancement> helmet_enhan;
	helmet_enhan.push_back(intelligence);
	helmet_enhan.push_back(wisdom);
	helmet_enhan.push_back(armor);

	//Adding armor allowed enhancements to vector
	vector<Enhancement> armor_enhan;
	armor_enhan.push_back(armor);

	//Adding shield allowed enhancements to vector
	vector<Enhancement> shield_enhan;
	shield_enhan.push_back(armor);

	//Adding ring allowed enhancements to vector
	vector<Enhancement> ring_enhan;
	ring_enhan.push_back(armor);
	ring_enhan.push_back(strength);
	ring_enhan.push_back(constitution);
	ring_enhan.push_back(wisdom);
	ring_enhan.push_back(armor);

	//Adding belt allowed enhancements to vector
	vector<Enhancement> belt_enhan;
	belt_enhan.push_back(constitution);
	belt_enhan.push_back(strength);

	//Adding boots allowed enhancements to vector
	vector<Enhancement> boots_enhan;
	boots_enhan.push_back(armor);
	boots_enhan.push_back(dexterity);

	//Adding weapon allowed enhancements to vector
	vector<Enhancement> weapon_enhan;
	weapon_enhan.push_back(attack);
	weapon_enhan.push_back(damage);

	//Creating a helmet object and assigning valid enhancements
	Item helmet_item("Helmet", helmet_enhan, "Beautiful Hat");

	//Creating a armor object and assigning valid enhancements
	Item armor_item("Armor", armor_enhan, "Beautiful Armor");

	//Creating a shield object and assigning valid enhancements
	Item shield_item("Shield", shield_enhan, "Beautiful Shield");

	//Creating a ring object and assigning valid enhancements
	Item ring_item("Ring", ring_enhan, "Beautiful Ring");

	//Creating a belt object and assigning valid enhancements
	Item belt_item("Belt", belt_enhan, "Beautiful Belt");

	//Creating a boots object and assigning valid enhancements
	Item boots_item("Boots", boots_enhan, "Beautiful Boots");

	//Creating a helmet object and assigning valid enhancements
	Item weapon_item("Weapon", weapon_enhan, "Beautiful Weapon");

    ///////////////////////////
    // INITIALIZING GUI DATA //
    ///////////////////////////

    Gui::font = Gui::fontGenerator.generateFont("GUI/fonts/EagleLake-Regular.ttf");

    sf::RenderWindow window(sf::VideoMode(Gui::W_HEIGHT, Gui::W_WIDTH), "comp345build", sf::Style::Close | sf::Style::Titlebar);

    Gui::emptyTexture.loadFromFile("GUI/textures/empty.png");
    Gui::wallTexture.loadFromFile("GUI/textures/wall.png");
    Gui::startTexture.loadFromFile("GUI/textures/start.png");
    Gui::exitTexture.loadFromFile("GUI/textures/exit.png");
    Gui::monsterTexture.loadFromFile("GUI/textures/monster.png");
    Gui::treasureTexture.loadFromFile("GUI/textures/treasure.png");
    Gui::characterTexture.loadFromFile("GUI/textures/character.png");
    Gui::friendlyTexture.loadFromFile("GUI/textures/friendly.png");

    ///////////////
    // GAME LOOP //
    ///////////////
    while (window.isOpen()) {
      window.clear(Gui::DARK_GRAY);

      //////////////////////
      // EVENT MANAGEMENT //
      //////////////////////
      sf::Event evt;
      while (window.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
          window.close();
        }
        GameData::eventManager->respondToRealTimeTypeFeedback(evt);
        GameData::eventManager->respondToSelectionBoxClick(window, evt);
        GameData::eventManager->respondToHomeButtonClick(window, evt);
        GameData::eventManager->respondToSaveMapCampaign(window, evt);
        GameData::eventManager->respondToFileSelectionClick(window, evt);
        GameData::eventManager->respondToMapSizeClick(window, evt);
        GameData::eventManager->respondToMapCreateOkButton(window, evt);
        GameData::eventManager->respondToMapTileSelect(window, evt);
        GameData::eventManager->respondToCampaignAvailableMapsClick(window, evt);
        GameData::eventManager->respondToCampaignMapOrderClick(window, evt);
        GameData::eventManager->respondToPlayingGameEvents(window, evt);
      }
      /////////////////////
      // SCENE SELECTION //
      /////////////////////
      if (Gui::isSelectingChoice)
        Gui::uiManager.isSelectingChoice(window);

      if (Gui::isSelectingMapSize)
        Gui::uiManager.isSelectingMapSize(window);

      if (Gui::isChoosingMapToCreate || Gui::isChoosingCampaignToCreate ||
          Gui::isChoosingCharacterToCreate || Gui::isChoosingItemToCreate) {
        Gui::uiManager.isTypingNameToCreate(window);
      }

      if (Gui::isChoosingMapToEdit || Gui::isChoosingCampaignToEdit ||
          Gui::isChoosingCharacterToEdit || Gui::isChoosingItemToEdit ||
          Gui::isChoosingCharacterToPlay || Gui::isChoosingCampaignToPlay ||
          Gui::isChoosingCampaignToPlay || Gui::isChoosingCharacterToPlay) {
        Gui::uiManager.isChoosingSomethingToEditOrPlay(window);
      }
      if (Gui::isEditingMap || Gui::isCreatingMap) {
        Gui::uiManager.isCreatingOrEditingMap(window);

        // special case: needs to be created after isCreatingOrEditingMp
        while (window.pollEvent(evt)) {
          GameData::eventManager->respondToMapBoxClick(window, evt);
        }
      }
      if (Gui::isCreatingCampaign || Gui::isEditingCampaign) {
        Gui::uiManager.isCreatingOrEditingCampaign(window);
      }

      if (Gui::isCreatingCharacter || Gui::isEditingCharacter) {
        Gui::uiManager.isCreatingOrEditingCharacter(window);
      }
      if (Gui::isPlayingGame) {
        for (int i = 0; i < (int)GameData::gameCharacters.size(); i++) {
          GameData::gameCharacters[i]->executeStrategy(*GameData::currentMapObject);
        }
        Gui::uiManager.isPlayingGame(window);
      }

      window.display();
    }

    return 0;
}


//int main() {

	//CharacterGenerator selectHero;
	////prompt player config
	//cout << endl << "Enter type of fighter (Bully, Tank, or Nimble) you wish you use: " << endl;
	//string fighterType1;
	//cin >> fighterType1;
	//cout << endl << "Enter the level of the character: " << endl;
	//int level1;
	//cin >> level1;
	//CharacterBuilder* playerBuilder = new PlayerCharacterBuilder(fighterType1, level1);
	////prompt enermy config
	//cout << endl << "Enter type of fighter (Bully, Tank, or Nimble) you wish your enermy to be: " << endl;
	//string fighterType2;
	//cin >> fighterType2;
	//cout << endl << "Enter the level of the character: " << endl;
	//int level2;
	//cin >> level2;
	//CharacterBuilder* enermyBuilder = new EnermyCharacterBuilder(fighterType2, level2);
	////config generator
	//selectHero.setCharacterBuilder(playerBuilder);
	//selectHero.createCharacter();
	//Character *player = selectHero.getCharacter();
	//selectHero.setCharacterBuilder(enermyBuilder);
	//selectHero.createCharacter();
	//Character *enermy = selectHero.getCharacter();
	////let's print!
	//srand(time(0));
	//cout << "Ok, here is what you have:" << endl;
	//cout << "Your character is a " << fighterType1 << endl;
	//cout << "with following stats: " << endl;
	//cout << "int " << player->getCharacterAttr()->getIntelligence() << " - "
		//<< "wis " << player->getCharacterAttr()->getWisdom() << " - "
		//<< "str " << player->getCharacterAttr()->getStrength() << " - "
		//<< "con " << player->getCharacterAttr()->getConstitution() << " - "
		//<< "dex " << player->getCharacterAttr()->getDexterity() << " - "
		//<< "cha " << player->getCharacterAttr()->getCharisma() << " - "
		//<< endl << "Hit Point at +" << player->getHitPoint() << endl;
	//cout << "Bonus attack at: " << endl;
	//for (int j = 0; j < 4; j++) {
		//cout << "round " << j << ": attack bonus + " << player->getAttackBonus()[j] << endl;
	//}
	//player->levelUp();
	//cout << "Now let's level up. After level up you have " << player->getHitPoint() << " hit points." << endl;
	//cout << "Bonus attack at: " << endl;
	//for (int k = 0; k < 4; k++) {
		//cout << "round " << k << ": attack bonus + " << player->getAttackBonus()[k] << endl;
	//}
	//cout << "Your enermy character is a " << fighterType2 << endl;
	//cout << "with following stats: " << endl;
	//cout << "int " << enermy->getCharacterAttr()->getIntelligence() << " - "
		//<< "wis " << enermy->getCharacterAttr()->getWisdom() << " - "
		//<< "str " << enermy->getCharacterAttr()->getStrength() << " - "
		//<< "con " << enermy->getCharacterAttr()->getConstitution() << " - "
		//<< "dex " << enermy->getCharacterAttr()->getDexterity() << " - "
		//<< "cha " << enermy->getCharacterAttr()->getCharisma() << " - "
		//<< endl << "Hit Point at +" << enermy->getHitPoint() << endl;
	//cout << "Bonus attack at: " << endl;
	//for (int j = 0; j < 4; j++) {
		//cout << "round " << j << ": attack bonus + " << enermy->getAttackBonus()[j] << endl;
	//}
	//enermy->levelUp();
	//cout << "Now let's level up. After level up you have " << enermy->getHitPoint() << " hit points." << endl;
	//cout << "Bonus attack at: " << endl;
	//for (int k = 0; k < 4; k++) {
		//cout << "round " << k << ": attack bonus + " << enermy->getAttackBonus()[k] << endl;
	//}
	////attack
	//cout << "you have hitpoint " << player->getHitPoint() << endl;
	//cout << "enermy has hitpoint " << enermy->getHitPoint() << endl;
	//cout << "you attack!" << endl;
	//player->attack(enermy);
	//cout << "you have hitpoint " << player->getHitPoint() << endl;
	//cout << "enermy has hitpoint " << enermy->getHitPoint() << endl;
	////prompt close console
	//int i = 1;
	//while (i == 1) {
		//cout << endl << "Enter 0 to quit the program." << endl;
		//cin >> i;
	//}
        //
        //




  //cout << "You are an adventurer 'S' on the map along with a friendly character 'C'." << endl;
  //cout << "Watch out, if you attack other characters, they might get angry and become aggresive ('O')..." << endl;

  //// Hardcoding a basic map
  //CharacterGenerator selectHero;
  //Map m(5,5,"S                C     O");
  //m.display();

  //// Initializing all characters on the map
  //vector<tuple<char,int,int>> characterPositions = m.getAllCharacterPositions();

  //for (int i = 0; i < (int)characterPositions.size(); i++) {
    //// Create a new one with appropriate position and type
    //char type; int posX; int posY;
    //tie(type, posX, posY) = characterPositions[i];
    //if (type == 'S') {
      //cout << "There is a human character at position ("<< posX << ","<< posY <<")" << endl;
      //CharacterBuilder* playerBuilder = new PlayerCharacterBuilder("Bully", 2);
      //selectHero.setCharacterBuilder(playerBuilder);
      //selectHero.createCharacter();
      //Character *player = selectHero.getCharacter();
      //vector<int> currentPosition = {posX,posY};
      //player->setCurrentPosition(currentPosition);
      //GameData::gameCharacters.push_back(player);
    //}
    //if (type == 'C') {
      //cout << "There is a friendly character at position ("<< posX << ","<< posY <<")" << endl;
      //CharacterBuilder* friendlyBuilder = new FriendlyCharacterBuilder("Tank", 4);
      //selectHero.setCharacterBuilder(friendlyBuilder);
      //selectHero.createCharacter();
      //Character *friendly = selectHero.getCharacter();
      //vector<int> currentPosition = {posX,posY};
      //friendly->setCurrentPosition(currentPosition);
      //GameData::gameCharacters.push_back(friendly);
    //}
    //if (type == 'O') {
      //cout << "There is an aggressor character at position ("<< posX << ","<< posY <<")" << endl;
      //CharacterBuilder* enermyBuilder = new EnermyCharacterBuilder("Nimble", 3);
      //selectHero.setCharacterBuilder(enermyBuilder);
      //selectHero.createCharacter();
      //Character *enermy = selectHero.getCharacter();
      //vector<int> currentPosition = {posX,posY};
      //enermy->setCurrentPosition(currentPosition);
      //GameData::gameCharacters.push_back(enermy);
    //}
  //}
  //cout << endl;

  //while (true) {
    //for (int i = 0; i < (int)GameData::gameCharacters.size(); i++) {
      //GameData::gameCharacters[i]->executeStrategy(m);
    //}
  //}


  //return 0;
//}

