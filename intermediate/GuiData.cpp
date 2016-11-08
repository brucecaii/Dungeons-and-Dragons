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
  const unsigned long BLOCK_THREAD_WAIT_TIME = 200;
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

  vector<string> current_maps;
  vector<sf::FloatRect> current_map_positions;
  vector<string> current_campaigns;
  vector<sf::FloatRect> current_campaign_positions;
  string chosenCampaign;
  string chosenMap;
  string createdCampaign = "";
  string createdMap = "";
  float greetingsTransparency = 0.0f;
  float callToActionTransparency = 0.0f;
  float selectionBoxTransparency = 0.0f;
  bool hasCreateMapPosition = false;
  bool hasEditMapPosition = false;
  bool hasCreateCampaignPosition = false;
  bool hasEditCampaignPosition = false;
  bool isSelectingChoice = true;
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
  bool shouldBlockThread = false;
  unsigned long msSinceStart;

  int tempMapWidth = 4;
  int tempMapLength = 4;
};

