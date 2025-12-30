//
//    LunokWatch, a open source smartwatch software
//    Copyright (C) 2022,2023  Jordi Rubió <jordi@binarycell.org>
//    This file is part of LunokWatch.
//
// LunokWatch is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software 
// Foundation, either version 3 of the License, or (at your option) any later 
// version.
//
// LunokWatch is distributed in the hope that it will be useful, but WITHOUT 
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
// details.
//
// You should have received a copy of the GNU General Public License along with 
// LunokWatch. If not, see <https://www.gnu.org/licenses/>. 
//

#include "../UI/AppLuITemplate.hpp"
#include "LuIMainMenu.hpp"
#include "../UI/controls/IconMenu.hpp"
#include "../UI/controls/base/Container.hpp"
#include "../UI/controls/Paginator.hpp"
#include "../UI/controls/Text.hpp"
#include "LogView.hpp"

//#include <LilyGoWatch.h>

#include "../resources.hpp"

#include "Battery.hpp"
#include "Notifications.hpp"
#include "About.hpp"
#include "Steps.hpp"
#include "Brightness.hpp"
#include "Activities.hpp"
#include "Calculator.hpp"
#include "Stopwatch.hpp"
#include "LuISettingsMenu.hpp"
#include "Calendar.hpp"
//#include "LuiExperiment.hpp"
//#include "LuITest.hpp"
//#include "LuIDemoRubiks.hpp"
//#include "ScreenTest.hpp"
#include "KnowLocations.hpp"
#include "LuiGamesMenu.hpp"
#include "LuaLauncher.hpp"
//#include "FileBrowser.hpp"
#ifdef LUNOKIOT_LILYGO_TWATCH_BUTTON_FAULTY
#include "Lamp.hpp"
#endif
//#include "PartitionBrowser.hpp"
//#include "LunoNoid.hpp"
//#include "Dungeon/Dungeon.hpp"
//#include "LuiChess.hpp"
#include "MostUsedApps.hpp"
#include "Provisioning2.hpp"
#include "FreehandKeyboardSetup.hpp"
#include "NuKeyboard.hpp"

using namespace LuI;

// Macro to reduce boilerplate for standard application menu items
// Creates an application instance, sets its back callback, and launches it
#define MENU_APP_ENTRY(label, imgbits, imgh, imgw, AppClass)        \
    {                                                                 \
        label,                                                        \
        imgbits,                                                      \
        imgh,                                                         \
        imgw,                                                         \
        [](IGNORE_PARAM) {                                            \
            AppClass * app = new AppClass();                          \
            app->backCallback = [](void * obj){                       \
                LaunchApplication(new LuIMainMenuApplication());      \
            };                                                        \
            LaunchApplication(app);                                   \
        }                                                             \
    }

// Static variable to remember last selected menu item
static int lastSelectedMenuEntry = 1;
static const int FIRST_MAIN_MENU_ENTRY_INDEX = 1;

const IconMenuEntry LuIMenuItems[] = {
    
    {"Back", img_mainmenu_back_bits, img_mainmenu_back_height, img_mainmenu_back_width, [](IGNORE_PARAM) { LaunchWatchface(); } },
//    MENU_APP_ENTRY("Prov",                                           img_mainmenu_provisioning_bits,    img_mainmenu_provisioning_height,    img_mainmenu_provisioning_width,    Provisioning2Application),
//    MENU_APP_ENTRY("NuKeyb",                                         img_mainmenu_keyboard_bits,        img_mainmenu_keyboard_height,        img_mainmenu_keyboard_width,        NuKeyboardApplication),
//    MENU_APP_ENTRY("Keyboard",                                       img_mainmenu_keyboard_bits,        img_mainmenu_keyboard_height,        img_mainmenu_keyboard_width,        FreeHandKeyboardSetupApplication),
//    MENU_APP_ENTRY("MostUsed",                                       img_mainmenu_debug_bits,           img_mainmenu_debug_height,           img_mainmenu_debug_width,           LuIMostUsedApplication),
//    MENU_APP_ENTRY("Chess",                                          img_mainmenu_chess_bits,           img_mainmenu_chess_height,           img_mainmenu_chess_width,           ChessApplication),
//    MENU_APP_ENTRY("Log",                                            img_mainmenu_cpu_bits,             img_mainmenu_cpu_height,             img_mainmenu_cpu_width,             LogViewApplication),
//    MENU_APP_ENTRY("Partitions",                                     img_mainmenu_partition_bits,       img_mainmenu_partition_height,       img_mainmenu_partition_width,       PartitionExplorerApplication),
//    MENU_APP_ENTRY("FileBrowser",                                    img_mainmenu_folder_bits,          img_mainmenu_folder_height,          img_mainmenu_folder_width,          FileExplorerApplication),
//    MENU_APP_ENTRY("Calendar",                                       img_mainmenu_calendar_bits,        img_mainmenu_calendar_height,        img_mainmenu_calendar_width,        CalendarApplication),
//    MENU_APP_ENTRY("Dungeon",                                        img_mainmenu_dungeon_bits,         img_mainmenu_dungeon_height,         img_mainmenu_dungeon_width,         DungeonGameApplication),
//    MENU_APP_ENTRY("LunoNoid",                                       img_mainmenu_lunonoid_bits,        img_mainmenu_lunonoid_height,        img_mainmenu_lunonoid_width,        LunoNoidGameApplication),
//    {"Lua",img_mainmenu_debug_bits, img_mainmenu_debug_height, img_mainmenu_debug_width, [](IGNORE_PARAM) { LaunchApplication(new LuaLauncher(HelloworldLuaScript)); } },
//    {"Screen",img_mainmenu_debug_bits, img_mainmenu_debug_height, img_mainmenu_debug_width, [&](IGNORE_PARAM) { LaunchApplication(new ScreenTestApplication()); } },
//    MENU_APP_ENTRY("Rubik's",                                        img_mainmenu_debug_bits,           img_mainmenu_debug_height,           img_mainmenu_debug_width,           LuIExperimentRubiksApplication),
//    MENU_APP_ENTRY("LuIDemos",                                       img_mainmenu_debug_bits,           img_mainmenu_debug_height,           img_mainmenu_debug_width,           LuiExperimentApplication),

    MENU_APP_ENTRY("Bright",                                         img_mainmenu_bright_bits,          img_mainmenu_bright_height,          img_mainmenu_bright_width,          BrightnessApplication),
#ifdef LUNOKIOT_LILYGO_TWATCH_BUTTON_FAULTY
    MENU_APP_ENTRY("Lamp",                                           img_mainmenu_lamp_bits,            img_mainmenu_lamp_height,            img_mainmenu_lamp_width,            LampApplication),
#endif
    MENU_APP_ENTRY("Notify",                                         img_mainmenu_notifications_bits,   img_mainmenu_notifications_height,   img_mainmenu_notifications_width,   NotificacionsApplication),
    MENU_APP_ENTRY("Steps",                                          img_mainmenu_steps_bits,           img_mainmenu_steps_height,           img_mainmenu_steps_width,           StepsApplication),
    MENU_APP_ENTRY("Stopwatch",                                      img_mainmenu_stopwatch_bits,       img_mainmenu_stopwatch_height,       img_mainmenu_stopwatch_width,       StopwatchApplication),
    MENU_APP_ENTRY("Settings",                                       img_mainmenu_options_bits,         img_mainmenu_options_height,         img_mainmenu_options_width,         LuISettingsMenuApplication),
    MENU_APP_ENTRY("Locations",                                      img_mainmenu_zone_bits,            img_mainmenu_zone_height,            img_mainmenu_zone_width,            KnowLocationApplication),
    MENU_APP_ENTRY("Calendar",                                       img_mainmenu_calendar_bits,        img_mainmenu_calendar_height,        img_mainmenu_calendar_width,        CalendarApplication),
    MENU_APP_ENTRY("Calculator",                                     img_mainmenu_calculator_bits,      img_mainmenu_calculator_height,      img_mainmenu_calculator_width,      CalculatorApplication),
    MENU_APP_ENTRY("Games",                                          img_mainmenu_games_bits,           img_mainmenu_games_height,           img_mainmenu_games_width,           LuIGamesMenuApplication),
    MENU_APP_ENTRY("Battery",                                        img_mainmenu_battery_bits,         img_mainmenu_battery_height,         img_mainmenu_battery_width,         BatteryApplication),
    MENU_APP_ENTRY("About",                                          img_mainmenu_about_bits,           img_mainmenu_about_height,           img_mainmenu_about_width,           AboutApplication),
};
int LuIMenuItemsNumber = sizeof(LuIMenuItems) / sizeof(LuIMenuItems[0])-1;


LuIMainMenuApplication::LuIMainMenuApplication() {
    directDraw = false; // disable direct draw meanwhile build the UI
    canvas->fillSprite(TFT_BLACK);
    
    // Create screen with 3 sections: paginator, menu, and entry text
    Container * screen = new Container(LuI_Horizontal_Layout, 3);
    
    // Setup paginator
    paginator = new Paginator(LuIMenuItemsNumber);
    paginator->border = 40;
    paginator->SetBackgroundColor(TFT_BLACK);
    screen->AddChild(paginator, 0.5);
    
    // Setup main menu
    mainMenu = new IconMenu(LuI_Horizontal_Layout, LuIMenuItemsNumber, LuIMenuItems);
    screen->AddChild(mainMenu, 2.0);
    
    // Setup entry text
    entryText = new Text((char*)"", TFT_WHITE, false, 1, &FreeMonoBold18pt7b);
    entryText->SetBackgroundColor(TFT_BLACK);
    screen->AddChild(entryText, 0.5);
    
    // Setup page callback to sync paginator and text with menu selection
    mainMenu->pageCallback = [&, this](IGNORE_PARAM) {
        paginator->SetCurrent(mainMenu->selectedEntry);
        entryText->SetText((char*)(LuIMenuItems[mainMenu->selectedEntry].name));
        lastSelectedMenuEntry = mainMenu->selectedEntry; // remember selection
    };
    
    // Restore last selected entry or default to first app (skip "Back")
    int selectedEntry = (lastSelectedMenuEntry > FIRST_MAIN_MENU_ENTRY_INDEX) ? lastSelectedMenuEntry : FIRST_MAIN_MENU_ENTRY_INDEX;
    mainMenu->selectedEntry = selectedEntry;
    paginator->SetCurrent(selectedEntry);
    entryText->SetText((char*)LuIMenuItems[selectedEntry].name);
    
    AddChild(screen);
    directDraw = true; // allow controls to sync itself with the screen
}
