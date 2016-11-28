#include "Map.h"
#include "Campaign.h"
#include "Character.h"
#include "Item.h"

namespace GameData {

  Map* currentMapObject = new Map();
  Campaign* currentCampaignObject = new Campaign();
  Character* currentCharacterObject = new Character();
  Item* currentItemObject = new Item();

}
