#include "Map/Map.h"
#include "Map/MapCampaign.h"
#include "Character/Character.h"
#include "Item/Item.h"
#include "GameLogger.h"
#include "GUI/Events.h"

namespace GameData {

  extern Map* currentMapObject;
  extern MapCampaign* currentCampaignObject;
  extern Fighter* currentCharacterObject;
  extern Item* currentItemObject;
  extern vector<Character*> gameCharacters;
  extern Dice* gameDice;
  extern Events* eventManager;

  //Logger
  extern GameLogger* diceLogger;
  extern GameLogger* eventLogger;
  extern GameLogger* mapLogger;
}

