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

#ifndef __LUNOKIOT__APPLICATION__LUI_MAINMENU__
#define __LUNOKIOT__APPLICATION__LUI_MAINMENU__

#include "../UI/AppLuITemplate.hpp"
#include "../UI/controls/Paginator.hpp"
#include "../UI/controls/Text.hpp"
#include "../UI/controls/IconMenu.hpp"

/**
 * @class LuIMainMenuApplication
 * @brief Main menu application for the LunokWatch smartwatch
 * 
 * Displays a paginated menu of available applications with icons and labels.
 * The application remembers the last selected menu item and restores it when
 * the user returns from a launched application.
 * 
 * Layout:
 * - Top: Paginator (dots indicating position in menu)
 * - Center: IconMenu (menu items with icons)
 * - Bottom: Text label showing current selection
 */
class LuIMainMenuApplication : public TemplateLuIApplication {
    public:
        LuI::Paginator * paginator;          ///< Paginator showing menu position
        LuI::Text      * entryText = nullptr;     ///< Text label of selected menu item
        LuI::IconMenu  * mainMenu;            ///< Main menu with icons
        LuIMainMenuApplication();
        const char *AppName() override { return "Main Menu"; };
};

#endif
