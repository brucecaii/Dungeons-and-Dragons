#include "../Map/Map.h"
#include "../Map/MapCampaign.h"
#include "../Character/Character.h"
#include "../Item/Item.h"

namespace GameData {

  Map* currentMapObject = new Map();
  MapCampaign* currentCampaignObject = new MapCampaign();
  Character* currentCharacterObject = new Character();
  Item* currentItemObject = new Item();

}
