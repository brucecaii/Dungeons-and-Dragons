#include <chrono>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "GuiData.h"
#include "Fonts.h"
#include "Texts.h"
#include "Events.h"
#include "Ui.h"

using namespace std::chrono;
using std::string;
using std::vector;

namespace GuiData {

  const sf::Color SELECTION_BACKGROUND_COLOR(40,42,54);
  const sf::Color ELLIPSIS_COLOR(189, 147, 249);

  const int WINDOW_HEIGHT = 800;
  const int WINDOW_WIDTH = 800;
  const int MAP_DISPLAY_WIDTH_LENGTH = 560;
  const float FADE_IN_STEP = 0.3f;
  const unsigned long UNIX_TIME_MS_START = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
  const unsigned long GREETINGS_APPEAR_TIME = 500;
  const unsigned long CALL_TO_ACTION_APPEAR_TIME = 2000;
  const unsigned long SELECTION_BOXES_APPEAR_TIME = 4000;
  const unsigned long BLOCK_THREAD_WAIT_TIME = 500;
  const float  TEXT_OUTLINE_THICKNESS = 0.3f;
  const sf::Vector2f mapAbsolutePositioning(60,120);
  Fonts fontGenerator;
  Texts textGenerator;
  Events eventManager;
  Ui uiManager;

  sf::Font currentFont;
  sf::FloatRect createMapPosition;
  sf::FloatRect editMapPosition;
  sf::FloatRect createCampaignPosition;
  sf::FloatRect editCampaignPosition;
  sf::FloatRect createCharacterPosition;
  sf::FloatRect editCharacterPosition;
  sf::FloatRect createItemPosition;
  sf::FloatRect editItemPosition;
  sf::FloatRect playPosition;
  sf::Text ellipsis;
  sf::Text greetings;
  sf::Text callToAction;
  sf::Text selectionBoxText;
  sf::Text selectMap;
  sf::Text typeMapName;
  sf::Text selectFileNames;
  sf::Text realTimeTypeFeedback;
  sf::Text NameConflictError;
  sf::Text HomeButton;
  sf::Text mapCreateOkButton;
  sf::Text selectMapSize;
  sf::Text saveButton;
  sf::Text widthIndicator;
  sf::Text widthPlus;
  sf::Text widthMinus;
  sf::Text lengthIndicator;
  sf::Text lengthPlus;
  sf::Text lengthMinus;
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
  sf::Sprite emptySelectionSprite;
  sf::Sprite wallSelectionSprite;
  sf::Sprite monsterSelectionSprite;
  sf::Sprite startSelectionSprite;
  sf::Sprite exitSelectionSprite;
  sf::Sprite treasureSelectionSprite;

  vector<string> current_maps;
  vector<string> current_characters;
  vector<string> current_items;
  vector<sf::FloatRect> current_map_positions;
  vector<sf::FloatRect> current_available_map_positions;
  vector<vector<sf::FloatRect>> currentMapTilePositions;
  vector<string> current_campaigns;
  vector<sf::FloatRect> current_campaign_positions;
  vector<string> current_campaign_map_order;
  vector<sf::FloatRect> current_campaign_map_order_positions;
  vector<sf::FloatRect> current_character_positions;
  vector<sf::FloatRect> current_item_positions;
  string playedCampaign;
  string playedCharacter;
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
  bool isSelectingChoice = true;
  bool hasCreateMapPosition = false;
  bool hasEditMapPosition = false;
  bool hasCreateCampaignPosition = false;
  bool hasEditCampaignPosition = false;
  bool hasCreateCharacterPosition = false;
  bool hasEditCharacterPosition = false;
  bool hasCreateItemPosition = false;
  bool hasEditItemPosition = false;
  bool hasPlayPosition= false;
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

  int tempMapWidth = 4;
  int tempMapLength = 4;
};


