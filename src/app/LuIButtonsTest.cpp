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
#include "LuIButtonsTest.hpp"
#include "../UI/controls/base/Container.hpp"
#include "../UI/controls/Button.hpp"
#include "../UI/controls/Text.hpp"
#include "../UI/controls/Image.hpp"
#include "../UI/controls/XBM.hpp"
#include "../UI/controls/View3D/View3D.hpp"

#include "../resources.hpp"

using namespace LuI;

DebugLuIButtonsApplication::DebugLuIButtonsApplication() {
    // Create standard layout with view container and back button bar
    // Use slightly different quotas to match original behavior
    LuIStandardLayout layout = CreateStandardLayout(1.7, 0.3);
    
    // creates the two columns of sample buttons
    Container * leftContainer= new Container(LuI_Horizontal_Layout,3);
    Container * rightContainer= new Container(LuI_Horizontal_Layout,3);
    
    // The layout.viewContainer has 1 slot by default, we need 2 slots
    // Create a new container with 2 slots for left/right columns
    Container * columnsContainer = new Container(LuI_Vertical_Layout, 2);
    columnsContainer->AddChild(leftContainer);
    columnsContainer->AddChild(rightContainer);
    layout.viewContainer->AddChild(columnsContainer);

    // fill viewContainer with different type of buttons
    
    // left view side <-----------------------------------

    // -----> text button
    LuI::Button *textButton = new LuI::Button(); // a basic default button
    textButton->AddChild(new Text("Hello"));
    leftContainer->AddChild(textButton);

    // -----> text button with font
    LuI::Button *textButtonAlt = new LuI::Button(); // a basic default button
    textButtonAlt->AddChild(new Text("Yep!",TFT_YELLOW,false,1,&FreeSerifItalic12pt7b));
    leftContainer->AddChild(textButtonAlt);

    // -----> xbm 1 bit image button
    LuI::Button *XBMButton = new LuI::Button();
    XBMButton->AddChild(new XBM(img_xbm_32_width,img_xbm_32_height,img_xbm_32_bits));
    leftContainer->AddChild(XBMButton);


    // right view side ----------------------------------->

    // -----> 16 bit image button with mask color
    LuI::Button *ImageButton = new LuI::Button();
    ImageButton->AddChild(new Image(img_house_32.width,img_house_32.height,img_house_32.pixel_data,TFT_GREEN));
    rightContainer->AddChild(ImageButton);

    // -----> using Container properties of Button to add two controls
    LuI::Button *CombinedButton = new LuI::Button(LuI_Vertical_Layout,2);
    CombinedButton->AddChild(new Image(img_house_32.width,img_house_32.height,img_house_32.pixel_data,TFT_GREEN),0.8);
    CombinedButton->AddChild(new Text("Home"),1.2);
    rightContainer->AddChild(CombinedButton);


    // -----> can compose with multiple other components, any control can be added
    LuI::Button *Button3d = new LuI::Button(LuI_Vertical_Layout,2);
    Mesh3D * sparkles = new Mesh3D(&BackButtonMesh); // load 3D mesh
    View3D * sparklesView = new View3D(); // create view for 3D mesh
    sparklesView->SetGlobalScale(0.15);  // mesh methers=pixels 240Meters=240pixels
    sparkles->Scale(0.15);
    sparklesView->SetGlobalRotation({float(random(0,360)),float(random(0,360)),float(random(0,360))}); // add some random
    sparklesView->SetBackgroundColor(ThCol(button));
    sparklesView->RenderMode = View3D::RENDER::FLAT; // set rendering to color cheaper-cpu one
    sparklesView->stepCallbackParam=sparklesView; // pass view to callback
    // *** see the coments in the bottom of this constructor: "sparklesView->dirty=true;"
    sparklesView->stepCallback = [](void * obj){ // callback when refresh is done
        View3D * self = (View3D *)obj;
        // want rotate the view
        Angle3D currentRot = self->GetGlobalRotation();
        currentRot.x+=5;
        currentRot.y+=5;
        currentRot.z+=5;
        self->SetGlobalRotation(currentRot);
        self->dirty=true;
    };
    sparklesView->AddMesh3D(sparkles);
    Button3d->AddChild(sparklesView,0.8);
    Button3d->AddChild(new Text("Home"),1.2);
    rightContainer->AddChild(Button3d);

    AddChild(layout.screen); // add root to view
    sparklesView->dirty=true; // why this?
    /* this is related with "step callback";
     * let me explain about "dirty" flag,
     * after AddChild call all GUI elements are updated and refreshed (don't need to refresh again)
     * this means, no elements refreshed again until someone is marked as dirty
     * the "sparklesView" uses "stepCallback" call, this means was called AFTER render
     * and the contents of callback updates the view Global rotation coordinates (marks as dirty)
     * creating a infinite loop, when the render is done, the mesh is updated, marked as dirty an called again
     * and mesh rotates infinitelly
     */
    directDraw=true; // allow controls to direct redraw itself instead of push whole view Sprite
    // Thats all! the app is running
}
