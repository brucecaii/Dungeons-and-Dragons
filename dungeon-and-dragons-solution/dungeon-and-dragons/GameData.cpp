#include "Map/Map.h"
#include "Map/MapCampaign.h"
#include "Character/Character.h"
#include "Item/Item.h"
#include "GameLogger.h"
#include "GUI/Events.h"

namespace GameData {

  Map* currentMapObject = new Map();
  MapCampaign* currentCampaignObject = new MapCampaign();
  Fighter* currentCharacterObject = new Fighter();
  Item* currentItemObject = new Item();
  vector<Fighter*> gameCharacters;
  vector<Fighter*> availableCharacters;
  vector<Fighter*> availablePlayers;
  vector<Fighter*> availableFriendlies;
  vector<Fighter*> availableAggressors;
  Dice* gameDice = new Dice();
  Events *eventManager = new Events();

  //Character Observer

  //Logging
  GameLogger *diceLogger = new GameLogger(gameDice, true);
  GameLogger *eventLogger = new GameLogger(eventManager, true);
  GameLogger *mapLogger = new GameLogger(currentMapObject, true);
  GameLogger *characterLogger = new GameLogger(currentCharacterObject, true);

}
