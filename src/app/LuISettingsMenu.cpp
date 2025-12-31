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
#include "LuISettingsMenu.hpp"
#include "../UI/controls/IconMenu.hpp"
#include "../UI/controls/base/Container.hpp"
#include "../UI/controls/Paginator.hpp"
#include "../UI/controls/Text.hpp"
#include "LogView.hpp"

//#include <LilyGoWatch.h>

#include "../resources.hpp"
#include "LuIMainMenu.hpp"

#include "Settings.hpp"
#include "Battery.hpp"
#include "Notifications.hpp"
#include "LuIRotation.hpp"
#include "Provisioning2.hpp"
#include "SetTime.hpp"
#include "SetTimeZone.hpp"
#include "Brightness.hpp"
#include "Advanced.hpp"
#include "Bluetooth.hpp"
#include "BLEMonitor.hpp"
#include "Theme.hpp"
#include "FreehandKeyboardSetup.hpp"
#include "GestureSettings.hpp"
#include "WatchfaceSelector.hpp"
#include "FileBrowser.hpp"
#include "PartitionBrowser.hpp"

using namespace LuI;

// Macro to reduce boilerplate for standard application menu items.
// Creates an application instance, sets its back callback to return to settings menu,
// and launches the application. This ensures consistent navigation behavior across
// all settings menu items.
//
// Parameters:
//   label     - Menu item label string
//   imgbits   - Bitmap data for the menu icon
//   imgh      - Icon height in pixels
//   imgw      - Icon width in pixels
//   AppClass  - Application class to instantiate
#define MENU_APP_ENTRY(label, imgbits, imgh, imgw, AppClass)        \
    {                                                                 \
        label,                                                        \
        imgbits,                                                      \
        imgh,                                                         \
        imgw,                                                         \
        [](IGNORE_PARAM) {                                            \
            AppClass * app = new AppClass();                          \
            app->backCallback = [](void * obj){                       \
                LaunchApplication(new LuISettingsMenuApplication()); \
            };                                                        \
            LaunchApplication(app);                                   \
        }                                                             \
    }

const int FIRST_SETTINGS_MENU_ENTRY_INDEX = 2;

const IconMenuEntry LuISettingsMenuItems[] = {
    {"Back",                                                         img_mainmenu_watchface_bits,       img_mainmenu_watchface_height,       img_mainmenu_watchface_width,       [](IGNORE_PARAM) { LaunchWatchface(); } },
    {"Back",                                                         img_mainmenu_back_bits,            img_mainmenu_back_height,            img_mainmenu_back_width,            [](IGNORE_PARAM) { LaunchApplication(new LuIMainMenuApplication()); } },
    MENU_APP_ENTRY("Radios",                                         img_mainmenu_wifi_bits,            img_mainmenu_wifi_height,            img_mainmenu_wifi_width,            SettingsApplication),
    MENU_APP_ENTRY("Gestures",                                       img_mainmenu_gesture_bits,         img_mainmenu_gesture_height,         img_mainmenu_gesture_width,         GestureSettings),
    MENU_APP_ENTRY("Watchface",                                      img_mainmenu_watchface_bits,       img_mainmenu_watchface_height,       img_mainmenu_watchface_width,       WatchfaceSelectorApplication),
    MENU_APP_ENTRY("Themes",                                         img_mainmenu_themes_bits,          img_mainmenu_themes_height,          img_mainmenu_themes_width,          ThemeApplication),
    MENU_APP_ENTRY("Pair",                                           img_mainmenu_bluetooth_bits,       img_mainmenu_bluetooth_height,       img_mainmenu_bluetooth_width,       BluetoothApplication),
    MENU_APP_ENTRY("Advanced",                                       img_mainmenu_cpu_bits,             img_mainmenu_cpu_height,             img_mainmenu_cpu_width,             AdvancedSettingsApplication),
    //MENU_APP_ENTRY("LittleFS",                                      img_mainmenu_folder_bits,          img_mainmenu_folder_height,          img_mainmenu_folder_width,          FileExplorerApplication),
    MENU_APP_ENTRY("Keyboard",                                       img_mainmenu_keyboard_bits,        img_mainmenu_keyboard_height,        img_mainmenu_keyboard_width,        FreeHandKeyboardSetupApplication),
    MENU_APP_ENTRY("BLEMonitor",                                     img_mainmenu_debug_bits,           img_mainmenu_debug_height,           img_mainmenu_debug_width,           BLEMonitorApplication),
    MENU_APP_ENTRY("Set time",                                       img_mainmenu_settime_bits,         img_mainmenu_settime_height,         img_mainmenu_settime_width,         SetTimeApplication),
    MENU_APP_ENTRY("Timezone",                                       img_timezone_120_bits,             img_timezone_120_height,             img_timezone_120_width,             SetTimeZoneApplication),
    MENU_APP_ENTRY("Prov",                                           img_mainmenu_provisioning_bits,    img_mainmenu_provisioning_height,    img_mainmenu_provisioning_width,    Provisioning2Application),
    MENU_APP_ENTRY("Rotation",                                       img_rotate_120_bits,               img_rotate_120_height,               img_rotate_120_width,               LuIRotateApplication),
    MENU_APP_ENTRY("Partitions",                                     img_mainmenu_partition_bits,       img_mainmenu_partition_height,       img_mainmenu_partition_width,       PartitionExplorerApplication),
};
int LuISettingsMenuItemsNumber = sizeof(LuISettingsMenuItems) / sizeof(LuISettingsMenuItems[0])-1;

// Static variable to remember last selected settings menu item
static int lastSelectedSettingsEntry = 2;

LuISettingsMenuApplication::LuISettingsMenuApplication() {
    directDraw = false;  // disable direct draw while building the UI
    canvas->fillSprite(TFT_BLACK);
    
    // Create screen with 3 sections: paginator, menu, and entry text
    Container * screen = new Container(LuI_Horizontal_Layout, 3);
    
    // Setup paginator
    paginator = new Paginator(LuISettingsMenuItemsNumber);
    paginator->border = 40;
    paginator->SetBackgroundColor(TFT_BLACK);
    screen->AddChild(paginator, 0.5);
    
    // Setup main menu
    mainMenu = new IconMenu(LuI_Horizontal_Layout, LuISettingsMenuItemsNumber, LuISettingsMenuItems);
    screen->AddChild(mainMenu, 2.0);
    
    // Setup entry text display
    entryText = new Text((char*)"", TFT_WHITE, false, 1, &FreeMonoBold18pt7b);
    entryText->SetBackgroundColor(TFT_BLACK);
    screen->AddChild(entryText, 0.5);
    
    // Setup page callback to sync paginator and text with menu selection
    mainMenu->pageCallbackParam = this;
    mainMenu->pageCallback = [](void * obj) {
        LuISettingsMenuApplication * self = (LuISettingsMenuApplication *)obj;
        self->paginator->SetCurrent(self->mainMenu->selectedEntry);
        self->entryText->SetText((char*)(LuISettingsMenuItems[self->mainMenu->selectedEntry].name));
        lastSelectedSettingsEntry = self->mainMenu->selectedEntry;  // remember selection
    };
    
    // Restore last selected entry or default to first app (skip "Back" entries at 0, 1)
    int selectedEntry = (lastSelectedSettingsEntry > FIRST_SETTINGS_MENU_ENTRY_INDEX) ? lastSelectedSettingsEntry : FIRST_SETTINGS_MENU_ENTRY_INDEX;
    mainMenu->selectedEntry = selectedEntry;
    paginator->SetCurrent(selectedEntry);
    entryText->SetText((char*)LuISettingsMenuItems[selectedEntry].name);
    
    AddChild(screen);
    directDraw = true;  // allow controls to sync with the screen
}
