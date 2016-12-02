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
  extern Enhancement* currentEnhancementObject;
  extern vector<Fighter*> gameCharacters;
  extern vector<Fighter*> availableCharacters;
  extern vector<Fighter*> availablePlayers;
  extern vector<Fighter*> availableFriendlies;
  extern vector<Fighter*> availableAggressors;
  extern Dice* gameDice;
  extern Events* eventManager;

  //Logger
  extern GameLogger* diceLogger;
  extern GameLogger* eventLogger;
  extern GameLogger* mapLogger;
}

