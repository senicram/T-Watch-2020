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
#include "LuiDialog.hpp"
#include "../UI/controls/XBM.hpp"
#include "../resources.hpp"

using namespace LuI;

LuIDialogApplication::LuIDialogApplication() {
    directDraw=false; // disable direct draw meanwhile build the UI
    // fill view with background color
    canvas->fillSprite(ThCol(background)); // use theme colors

    /// create root container with two slots horizontal
    screen = new Container(LuI_Horizontal_Layout,2);
    // bottom buttons container
    Container * bottomButtonContainer = new Container(LuI_Vertical_Layout,2);

    // main view space
    Container * viewContainer = new Container(LuI_Horizontal_Layout,2);

    // if use quota, all the slot quotas must sum equal the total number of elements
    // example: default quota in 2 controls result 50/50% of view space with 1.0 of quota everyone (2.0 in total)

    // add main view with quota of 1.7
    screen->AddChild(viewContainer,1.7);
    // add bottom button bar shirnked
    screen->AddChild(bottomButtonContainer,0.3);
    // 1.7 + 0.3 = 2.0 of quota (fine for 2 slots)

    // add back button to dismiss
    LuI::Button *backButton = new LuI::Button(LuI_Vertical_Layout,1,NO_DECORATION);
    backButton->tapCallback=[](void * obj){ LaunchWatchface(); }; // callback when tap
    // load icon in XBM format
    XBM * backButtonIcon = new XBM(img_backscreen_24_width,img_backscreen_24_height,img_backscreen_24_bits);
    // put the icon inside the button
    backButton->AddChild(backButtonIcon);
    // shrink button to left and empty control oversized (want button on left bottom)
    bottomButtonContainer->AddChild(backButton,0.3);
    bottomButtonContainer->AddChild(nullptr,1.7);


    dialogContents = new Text(""); 
    viewContainer->AddChild(dialogContents,1.4);

    Container * responseContainer = new Container(LuI_Vertical_Layout,2);

    noButton = new LuI::Button(); // a basic default button
    noButton->AddChild(new Text("No"));
    responseContainer->AddChild(noButton);
    yesButton = new LuI::Button(); // a basic default button
    yesButton->AddChild(new Text("Yes"));
    responseContainer->AddChild(yesButton);
    viewContainer->AddChild(responseContainer,0.6);

    AddChild(screen); // add root to view
    directDraw=true;

}
