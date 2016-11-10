#include "Texts.h"
#include "Events.h"
#include "Fonts.h"
#include "Ui.h"

namespace GuiData{

  extern const sf::Color SELECTION_BACKGROUND_COLOR;
  extern const sf::Color ELLIPSIS_COLOR;

  extern const int WINDOW_HEIGHT;
  extern const int WINDOW_WIDTH;
  extern const int MAP_DISPLAY_WIDTH_LENGTH;
  extern const float FADE_IN_STEP;
  extern const unsigned long UNIX_TIME_MS_START;
  extern const unsigned long GREETINGS_APPEAR_TIME;
  extern const unsigned long CALL_TO_ACTION_APPEAR_TIME;
  extern const unsigned long SELECTION_BOXES_APPEAR_TIME;
  extern const unsigned long BLOCK_THREAD_WAIT_TIME;
  extern const float TEXT_OUTLINE_THICKNESS;
  extern const sf::Vector2f mapAbsolutePositioning;

  extern Fonts fontGenerator;
  extern Texts textGenerator;
  extern Events eventManager;
  extern Ui uiManager;

  extern sf::Font currentFont;
  extern sf::FloatRect createMapPosition;
  extern sf::FloatRect editMapPosition;
  extern sf::FloatRect createCampaignPosition;
  extern sf::FloatRect editCampaignPosition;
  extern sf::FloatRect createCharacterPosition;
  extern sf::FloatRect editCharacterPosition;
  extern sf::FloatRect createItemPosition;
  extern sf::FloatRect editItemPosition;
  extern sf::FloatRect playPosition;
  extern sf::Text ellipsis;
  extern sf::Text greetings;
  extern sf::Text callToAction;
  extern sf::Text selectionBoxText;
  extern sf::Text selectMap;
  extern sf::Text typeMapName;
  extern sf::Text selectFileNames;
  extern sf::Text realTimeTypeFeedback;
  extern sf::Text NameConflictError;
  extern sf::Text selectMapSize;
  extern sf::Text HomeButton;
  extern sf::Text saveButton;
  extern sf::Text mapCreateOkButton;
  extern sf::Text widthIndicator;
  extern sf::Text widthPlus;
  extern sf::Text widthMinus;
  extern sf::Text lengthIndicator;
  extern sf::Text lengthPlus;
  extern sf::Text lengthMinus;
  extern sf::Text currentMapTileSelected;
  extern sf::Text campaignAvailableMapsText;
  extern sf::Text campaignMapOrderText;
  extern sf::Text campaignAvailableMaps;
  extern sf::Text campaignMapOrder;
  extern sf::Text mapValidationError;
  extern sf::Text campaignValidationError;
  extern sf::Text characterValidationError;
  extern sf::Text itemValidationError;


  extern char currentMapTileSelectedChar;
  extern sf::RectangleShape selectionBox;

  extern sf::Texture wallTexture;
  extern sf::Texture startTexture;
  extern sf::Texture exitTexture;
  extern sf::Texture monsterTexture;
  extern sf::Texture treasureTexture;
  extern sf::Texture emptyTexture;
  extern sf::Texture characterTexture;
  extern sf::Sprite emptySelectionSprite;
  extern sf::Sprite wallSelectionSprite;
  extern sf::Sprite monsterSelectionSprite;
  extern sf::Sprite characterSelectionSprite;
  extern sf::Sprite startSelectionSprite;
  extern sf::Sprite exitSelectionSprite;
  extern sf::Sprite treasureSelectionSprite;

  extern string chosenMap;
  extern string chosenCampaign;
  extern string chosenItem;
  extern string chosenCharacter;
  extern string createdCampaign;
  extern string createdCharacter;
  extern string createdItem;
  extern string createdMap;
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
  extern float greetingsTransparency;
  extern float callToActionTransparency;
  extern float selectionBoxTransparency;
  extern bool hasCreateMapPosition;
  extern bool hasEditMapPosition;
  extern bool hasCreateCampaignPosition;
  extern bool hasEditCampaignPosition;
  extern bool hasCreateCharacterPosition;
  extern bool hasEditCharacterPosition;
  extern bool hasCreateItemPosition;
  extern bool hasEditItemPosition;
  extern bool hasPlayPosition;
  extern bool isSelectingChoice;
  extern bool isSelectingMapSize;
  extern bool isChoosingMapToCreate;
  extern bool isChoosingMapToEdit;
  extern bool isChoosingCampaignToCreate;
  extern bool isChoosingCampaignToEdit;
  extern bool isEditingCampaign;
  extern bool isEditingMap;
  extern bool isCreatingCampaign;
  extern bool isCreatingMap;
  extern bool isChoosingCharacterToCreate;
  extern bool isChoosingCharacterToEdit;
  extern bool isChoosingItemToCreate;
  extern bool isChoosingItemToEdit;
  extern bool isChoosingMapToPlay;
  extern bool shouldBlockThread;
  extern bool isMapValid;
  extern bool shouldShowNameConflictError;
  extern bool shouldShowCampaignValidationError;
  extern bool shouldShowMapValidationError;
  extern bool shouldShowCharacterValidationError;
  extern bool shouldShowItemValidationError;
  extern unsigned long msSinceStart;

  extern int tempMapWidth;
  extern int tempMapLength;
};


