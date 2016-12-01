#include <chrono>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Gui.h"
#include "Fonts.h"
#include "Events.h"
#include "Ui.h"
#include "../GameLogger.h"

using namespace std::chrono;
using std::string;
using std::vector;

namespace Gui{

  const sf::Color DARK_GRAY(40,42,54);
  const sf::Color LIGHT_GRAY(68,71,90);
  const sf::Color WHITE(248, 248, 242);
  const sf::Color PURPLE(189, 147, 249);
  const sf::Color PINK(255, 121, 198);
  const sf::Color RED(255, 85, 85);
  const sf::Color TRANSPARENT(0, 0, 0, 0);

  const int W_HEIGHT = 800;
  const int W_WIDTH = 800;
  const int MAP_DISPLAY_WIDTH_LENGTH = 560;
  const unsigned long BLOCK_THREAD_WAIT_TIME = 500;
  const sf::Vector2f mapAbsolutePositioning(330,470);
  Fonts fontGenerator;
  Events *eventManager = new Events();
  //Events Logger
  GameLogger *eventLogger = new GameLogger(eventManager, true);
  Ui uiManager;

  sf::Font font;
  sf::Text text;
  sf::RectangleShape box;
  sf::Sprite sprite;

  // General button positions
  sf::FloatRect homeButtonPosition;
  sf::FloatRect saveButtonPosition;

  sf::FloatRect createMapPosition;
  sf::FloatRect editMapPosition;
  sf::FloatRect createCampaignPosition;
  sf::FloatRect editCampaignPosition;
  sf::FloatRect createCharacterPosition;
  sf::FloatRect editCharacterPosition;
  sf::FloatRect createItemPosition;
  sf::FloatRect editItemPosition;
  sf::FloatRect playPosition;

  sf::FloatRect widthPlusPosition;
  sf::FloatRect widthMinusPosition;
  sf::FloatRect lengthPlusPosition;
  sf::FloatRect lengthMinusPosition;
  sf::FloatRect mapCreateOkPosition;

  sf::FloatRect wallSelectionSpritePosition;
  sf::FloatRect exitSelectionSpritePosition;
  sf::FloatRect startSelectionSpritePosition;
  sf::FloatRect treasureSelectionSpritePosition;
  sf::FloatRect monsterSelectionSpritePosition;
  sf::FloatRect emptySelectionSpritePosition;
  sf::FloatRect friendlySelectionSpritePosition;
  sf::FloatRect mapBorderPosition;


  sf::Text selectMap;
  sf::Text typeMapName;
  sf::Text selectFileNames;
  sf::Text realTimeTypeFeedback;
  sf::Text NameConflictError;
  sf::Text HomeButton;
  sf::Text selectMapSize;
  sf::Text currentMapTileSelected;
  sf::Text campaignAvailableMapsText;
  sf::Text campaignMapOrderText;
  sf::Text campaignAvailableMaps;
  sf::Text campaignMapOrder;
  sf::Text mapValidationError;
  sf::Text campaignValidationError;
  sf::Text characterValidationError;
  sf::Text itemValidationError;
  sf::Text characterValuePrompt;

  sf::Texture wallTexture;
  sf::Texture startTexture;
  sf::Texture exitTexture;
  sf::Texture monsterTexture;
  sf::Texture treasureTexture;
  sf::Texture emptyTexture;
  sf::Texture characterTexture;
  sf::Texture friendlyTexture;

  vector<string> current_maps;
  vector<string> current_characters;
  vector<string> current_items;
  vector<string> current_campaigns;

  vector<sf::FloatRect> current_map_positions;
  vector<sf::FloatRect> current_available_map_positions;
  vector<vector<sf::FloatRect>> currentMapTilePositions;
  vector<sf::FloatRect> current_campaign_positions;
  vector<string> current_campaign_map_order;
  vector<sf::FloatRect> current_campaign_map_order_positions;
  vector<sf::FloatRect> current_character_positions;
  vector<sf::FloatRect> current_item_positions;
  string playedCampaign;
  string playedCharacter;
  string playedMap;
  string chosenCampaign;
  string chosenMap;
  string chosenItem;
  string chosenCharacter;
  string createdCampaign = "";
  string createdMap = "";
  string createdCharacter = "";
  string createdCharacterArgs = "";
  string chosenCharacterArgs = "";
  string createdItem = "";
  float greetingsTransparency = 0.0f;
  float callToActionTransparency = 0.0f;
  float selectionBoxTransparency = 0.0f;
  bool hasReachedEndOfMap = false;
  bool isSelectingChoice = true;
  bool isPlayingGame = false;
  bool isSelectingMapSize = false;
  bool isChoosingMapToCreate = false;
  bool isChoosingMapToEdit = false;
  bool isChoosingCampaignToCreate = false;
  bool isChoosingCampaignToEdit = false;
  bool isEditingCampaign = false;
  bool isEditingMap = false;
  bool isCreatingCampaign = false;
  bool isCreatingMap = false;
  bool shouldShowNameConflictError = false;
  bool isMapValid = false;
  bool isChoosingCharacterToCreate = false;
  bool isChoosingCharacterToEdit = false;
  bool isChoosingItemToCreate = false;
  bool isChoosingItemToEdit = false;
  bool isChoosingCampaignToPlay = false;
  bool isChoosingCharacterToPlay = false;
  bool isCreatingCharacter = false;
  bool isCreatingItem = false;
  bool isEditingCharacter = false;
  bool isEditingItem = false;
  bool shouldBlockThread = false;
  bool shouldShowCampaignValidationError = false;
  bool shouldShowMapValidationError = false;
  bool shouldShowCharacterValidationError = false;
  bool shouldShowItemValidationError = false;
  char currentMapTileSelectedChar = ' ';
  unsigned long msSinceStart;
  int GamePlayCurrentMap = 0;

  int tempMapWidth = 4;
  int tempMapLength = 4;
};


