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
  extern sf::RectangleShape selectionBox;

  extern string chosenMap;
  extern string chosenCampaign;
  extern string createdCampaign;
  extern string createdMap;
  extern vector<string> current_maps;
  extern vector<sf::FloatRect> current_map_positions;
  extern vector<string> current_campaigns;
  extern vector<sf::FloatRect> current_campaign_positions;
  extern float greetingsTransparency;
  extern float callToActionTransparency;
  extern float selectionBoxTransparency;
  extern bool hasCreateMapPosition;
  extern bool hasEditMapPosition;
  extern bool hasCreateCampaignPosition;
  extern bool hasEditCampaignPosition;
  extern bool isSelectingChoice;
  extern bool isSelectingMapSize;
  extern bool isChoosingMapToCreate;
  extern bool isChoosingMapToEdit;
  extern bool isChoosingCampaignToCreate;
  extern bool isChoosingCampaignToEdit;
  extern bool isEditingCampaign;
  extern bool isEditingMap;
  extern bool shouldShowNameConflictError;
  extern bool isCreatingCampaign;
  extern bool isCreatingMap;
  extern bool shouldBlockThread;
  extern unsigned long msSinceStart;

  extern int tempMapWidth;
  extern int tempMapLength;
};


