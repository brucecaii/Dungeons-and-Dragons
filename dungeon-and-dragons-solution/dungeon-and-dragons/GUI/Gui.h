#include "Events.h"
#include "Fonts.h"
#include "Ui.h"
#include "../Character/Fighter.h"

namespace Gui{

  extern const sf::Color DARK_GRAY;
  extern const sf::Color LIGHT_GRAY;
  extern const sf::Color WHITE;
  extern const sf::Color PURPLE;
  extern const sf::Color PINK;
  extern const sf::Color RED;
  extern const sf::Color TRANSPARENT;

  extern const int W_HEIGHT;
  extern const int W_WIDTH;
  extern const int MAP_DISPLAY_WIDTH_LENGTH;
  extern const unsigned long BLOCK_THREAD_WAIT_TIME;
  extern const sf::Vector2f mapAbsolutePositioning;
  extern Fonts fontGenerator;
  extern Ui uiManager;
  extern vector<Item*> tempItems;

  extern sf::Font font;
  extern sf::Text text;
  extern sf::RectangleShape box;
  extern sf::Sprite sprite;

  extern sf::FloatRect homeButtonPosition;
  extern sf::FloatRect saveButtonPosition;

  extern sf::FloatRect createMapPosition;
  extern sf::FloatRect consoleButtonPosition;
  extern sf::FloatRect editMapPosition;
  extern sf::FloatRect createCampaignPosition;
  extern sf::FloatRect editCampaignPosition;
  extern sf::FloatRect createCharacterPosition;
  extern sf::FloatRect editCharacterPosition;
  extern sf::FloatRect createItemPosition;
  extern sf::FloatRect editItemPosition;
  extern sf::FloatRect playPosition;

  extern sf::FloatRect widthPlusPosition;
  extern sf::FloatRect widthMinusPosition;
  extern sf::FloatRect lengthPlusPosition;
  extern sf::FloatRect lengthMinusPosition;
  extern sf::FloatRect mapCreateOkPosition;




  extern sf::FloatRect mapBorderPosition;


  extern sf::Text selectMap;
  extern sf::Text typeMapName;
  extern sf::Text selectFileNames;
  extern sf::Text realTimeTypeFeedback;
  extern sf::Text NameConflictError;
  extern sf::Text HomeButton;
  extern sf::Text selectMapSize;
  extern sf::Text currentMapTileSelected;
  extern sf::Text campaignAvailableMapsText;
  extern sf::Text campaignMapOrderText;
  extern sf::Text campaignAvailableMaps;
  extern sf::Text campaignMapOrder;
  extern sf::Text mapValidationError;
  extern sf::Text campaignValidationError;
  extern sf::Text characterValidationError;
  extern sf::Text itemValidationError;
  extern sf::Text characterValuePrompt;

  extern sf::Texture wallTexture;
  extern sf::Texture startTexture;
  extern sf::Texture exitTexture;
  extern sf::Texture monsterTexture;
  extern sf::Texture treasureTexture;
  extern sf::Texture emptyTexture;
  extern sf::Texture characterTexture;
  extern sf::Texture friendlyTexture;
  extern sf::FloatRect emptySelectionSpritePosition;
  extern sf::FloatRect wallSelectionSpritePosition;
  extern sf::FloatRect monsterSelectionSpritePosition;
  extern sf::FloatRect startSelectionSpritePosition;
  extern sf::FloatRect exitSelectionSpritePosition;
  extern sf::FloatRect treasureSelectionSpritePosition;
  extern sf::FloatRect friendlySelectionSpritePosition;

  extern vector<string> current_maps;
  extern vector<string> current_characters;
  extern vector<string> current_items;
  extern vector<sf::FloatRect> current_map_positions;
  extern vector<sf::FloatRect> current_available_map_positions;
  extern vector<vector<sf::FloatRect>> currentMapTilePositions;
  extern vector<string> current_campaigns;
  extern vector<sf::FloatRect> current_campaign_positions;
  extern vector<string> current_campaign_map_order;
  extern vector<sf::FloatRect> current_campaign_map_order_positions;
  extern vector<sf::FloatRect> current_character_positions;
  extern vector<sf::FloatRect> current_item_positions;
  extern vector<sf::FloatRect> current_equipped_item_positions;
  extern string playedCampaign;
  extern string playedCharacter;
  extern string playedMap;
  extern string chosenCampaign;
  extern string chosenMap;
  extern string chosenItem;
  extern string chosenCharacter;
  extern string createdCampaign;
  extern string createdMap;
  extern string createdCharacter;
  extern string createdCharacterArgs;
  extern string chosenCharacterArgs;
  extern string createdItemArgs;
  extern string chosenItemArgs;
  extern string createdItem;
  extern bool shouldShowPlayerTypeError;
  extern bool hasReachedEndOfMap;
  extern bool isSelectingChoice;
  extern bool isPlayingGame;
  extern bool isSelectingMapSize;
  extern bool isChoosingMapToCreate;
  extern bool isChoosingMapToEdit;
  extern bool isChoosingCampaignToCreate;
  extern bool isChoosingCampaignToEdit;
  extern bool isEditingCampaign;
  extern bool isEditingMap;
  extern bool isCreatingCampaign;
  extern bool isCreatingMap;
  extern bool shouldShowNameConflictError;
  extern bool isMapValid;
  extern bool isChoosingCharacterToCreate;
  extern bool isChoosingCharacterToEdit;
  extern bool isChoosingItemToCreate;
  extern bool isChoosingItemToEdit;
  extern bool isChoosingCampaignToPlay;
  extern bool isChoosingCharacterToPlay;
  extern bool isCreatingCharacter;
  extern bool isCreatingItem;
  extern bool isEditingCharacter;
  extern bool isEditingItem;
  extern bool shouldShowCampaignValidationError;
  extern bool shouldShowMapValidationError;
  extern bool shouldShowCharacterValidationError;
  extern bool shouldShowItemValidationError;
  extern char currentMapTileSelectedChar;
  extern unsigned long msSinceStart;
  extern int GamePlayCurrentMap;

  extern int tempMapWidth;
  extern int tempMapLength;

  extern vector<Fighter*> tempGameCharacters;
  extern Fighter* tempCharacter;
};

