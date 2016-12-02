#pragma once
#include "Character/CharacterGenerator.h"
#include "Map/Map.h"
#include "GameData.h"
#include "Character/AggressorStrategy.h"
#include "Character/FriendlyStrategy.h"
#include "Character/HumanPlayerStrategy.h"
#include "GUI/Gui.h"
#include "CharacterObserver.h"

class ConsoleActions {
public:
	static void initializeCharacterViews();
	static void consoleGameplayOptions();
	static void triggerInventoryView();
	static void triggerCharacterView();
	static void TogglingLogger();
};
