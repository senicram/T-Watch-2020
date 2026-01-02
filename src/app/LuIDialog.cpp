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
#include "LuIDialog.hpp"
#include "../UI/controls/XBM.hpp"
#include "../UI/controls/Button.hpp"
#include "../UI/controls/Text.hpp"
#include "../resources.hpp"

using namespace LuI;

LuIDialogApplication::LuIDialogApplication() {
    // Create standard layout with view container and back button bar
    LuIStandardLayout layout = CreateStandardLayout(1.7, 0.3);
    screen = layout.screen;
    
    // Create main view with 2 horizontal slots (text + response buttons)
    Container * viewContainer = new Container(LuI_Horizontal_Layout, 2);

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

    // Replace the view container in the layout
    layout.screen->AddChild(viewContainer, 1.7);

    AddChild(screen); // add root to view
    directDraw=true;

}
