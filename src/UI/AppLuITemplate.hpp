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

#ifndef __LUNOKIOT__CHANGEME_LUI_APP__
#define __LUNOKIOT__CHANGEME_LUI_APP__

#include "../system/Application.hpp"
#include "../UI/controls/base/Control.hpp"
#include "../UI/controls/base/Container.hpp"

namespace LuI {
    class Button;
}

// Structure to hold the standard screen layout components
struct LuIStandardLayout {
    LuI::Container * screen;
    LuI::Container * viewContainer;
    LuI::Container * bottomButtonContainer;
    LuI::Button * backButton;
};

class TemplateLuIApplication : public LunokIoTApplication {
    protected:
        LuI::Container * child=nullptr;
        LuI::Container * GetChild() { return child; }
        void AddChild(INOUT LuI::Container *control );
        void EventHandler();
        
        // Helper to create a standard screen layout with view container and back button bar
        // Returns all created containers for customization
        // Parameters:
        //   viewQuota: space ratio for main view (default 1.65 out of 2.0)
        //   bottomQuota: space ratio for bottom bar (default 0.35 out of 2.0)
        //   backgroundColor: background color (default theme background)
        LuIStandardLayout CreateStandardLayout(
            float viewQuota = 1.65,
            float bottomQuota = 0.35,
            uint16_t backgroundColor = 0xFFFF  // 0xFFFF means use theme default
        );
        
        // Helper to create a standard back button with icon
        // Returns the created button for callback customization
        // Parameters:
        //   useSmallIcon: if true uses 24px icon, otherwise 42px icon
        //   border: button border size (default 10)
        LuI::Button * CreateBackButton(bool useSmallIcon = true, uint8_t border = 10);
        
    public:
        const char *AppName() override { return "AppTemplateLuI without name"; };
        TemplateLuIApplication();
        ~TemplateLuIApplication();
        virtual bool Tick();
};

#endif
