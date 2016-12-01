#include "Map/Map.h"
#include "Map/MapCampaign.h"
#include "Character/Character.h"
#include "Item/Item.h"
#include "GameLogger.h"

namespace GameData {

  Map* currentMapObject = new Map();
  MapCampaign* currentCampaignObject = new MapCampaign();
  Character* currentCharacterObject = new Character();
  Item* currentItemObject = new Item();
  vector<Character*> gameCharacters;
  Dice* gameDice = new Dice();

  //Logging
  GameLogger* diceLogger = new GameLogger(gameDice, true);
}
