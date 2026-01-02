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

#include <Arduino.h>
#include "../app/LogView.hpp" // log capabilities
#include "../UI/AppLuITemplate.hpp"
#include "../UI/UI.hpp"
#include "../UI/controls/base/Control.hpp"
#include "../UI/controls/base/Container.hpp"
#include "../UI/controls/Image.hpp"
#include "../UI/controls/Text.hpp"
#include "../UI/controls/Button.hpp"
#include "../UI/controls/XBM.hpp"
#include "../UI/controls/Check.hpp"
#include "../resources.hpp"

extern bool UILongTapOverride;

TemplateLuIApplication::TemplateLuIApplication() {
    UILongTapOverride=true;
    directDraw=false;
}

TemplateLuIApplication::~TemplateLuIApplication() {
    if (nullptr != child ) { delete child; child=nullptr; }
}

void TemplateLuIApplication::EventHandler() {
    if (nullptr == child ) { return; }
    child->EventHandler();
}

bool TemplateLuIApplication::Tick() {
    EventHandler();
    return false; // is directDraw application
}

void TemplateLuIApplication::AddChild(INOUT LuI::Container *control ) {
    lAppLog("ADDCHILD BEGIN CONSTRUCTOR HERE\n");
    child=control;
    child->SetSize(canvas->width(),canvas->height());
    child->Refresh(false); // force get first frame
    // push to my canvas
    TFT_eSprite * currentView = child->GetCanvas();
    currentView->setPivot(0,0);
    canvas->setPivot(0,0);
    currentView->pushRotated(canvas,0,Drawable::MASK_COLOR); // push to app view
    lAppLog("ADDCHILD END CONSTRUCTOR HERE\n");
}

LuI::Button * TemplateLuIApplication::CreateBackButton(bool useSmallIcon, uint8_t border) {
    LuI::Button *backButton = new LuI::Button(LuI_Vertical_Layout, 1, NO_DECORATION);
    backButton->border = border;
    backButton->tapCallback = [](void * obj) { LaunchWatchface(); };
    
    LuI::XBM *backButtonIcon;
    if (useSmallIcon) {
        backButtonIcon = new LuI::XBM(img_backscreen_24_width, img_backscreen_24_height, img_backscreen_24_bits);
    } else {
        backButtonIcon = new LuI::XBM(img_backscreen_42_width, img_backscreen_42_height, img_backscreen_42_bits);
    }
    backButton->AddChild(backButtonIcon);
    
    return backButton;
}

LuIStandardLayout TemplateLuIApplication::CreateStandardLayout(
    float viewQuota,
    float bottomQuota,
    uint16_t backgroundColor
) {
    LuIStandardLayout layout;
    
    // Use theme background if 0xFFFF is passed (marker for default)
    uint16_t bgColor = (backgroundColor == 0xFFFF) ? ThCol(background) : backgroundColor;
    canvas->fillSprite(bgColor);
    
    // Create root container with two slots horizontal
    layout.screen = new LuI::Container(LuI_Horizontal_Layout, 2);
    
    // Bottom buttons container
    layout.bottomButtonContainer = new LuI::Container(LuI_Vertical_Layout, 2);
    
    // Main view space
    layout.viewContainer = new LuI::Container(LuI_Horizontal_Layout, 1);
    
    // Add main view with specified quota
    layout.screen->AddChild(layout.viewContainer, viewQuota);
    // Add bottom button bar
    layout.screen->AddChild(layout.bottomButtonContainer, bottomQuota);
    
    // Create back button
    layout.backButton = CreateBackButton(true, 10);
    
    // Add back button to bottom left
    layout.bottomButtonContainer->AddChild(layout.backButton, bottomQuota);
    // Add empty space on right (caller can replace this with custom content if needed)
    layout.bottomButtonContainer->AddChild(nullptr, viewQuota);
    
    return layout;
}
