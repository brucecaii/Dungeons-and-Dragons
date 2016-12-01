#include "Map/Map.h"
#include "Map/MapCampaign.h"
#include "Character/Character.h"
#include "Item/Item.h"
#include "GameLogger.h"

namespace GameData {

  extern Map* currentMapObject;
  extern MapCampaign* currentCampaignObject;
  extern Character* currentCharacterObject;
  extern Item* currentItemObject;
  extern vector<Character*> gameCharacters;
  extern Dice* gameDice;
  
  //Logger
  extern GameLogger* diceLogger;
}

