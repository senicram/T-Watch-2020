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
#include "LuIBufferTest.hpp"
#include "../UI/controls/base/Container.hpp"
#include "../UI/controls/Button.hpp"
#include "../UI/controls/Text.hpp"
#include "../UI/controls/Image.hpp"
#include "../UI/controls/XBM.hpp"
#include "../UI/controls/View3D/View3D.hpp"
#include "../UI/controls/Buffer.hpp"

#include "../resources.hpp"

using namespace LuI;

LuIBufferTestApplication::LuIBufferTestApplication() {
    // Create standard layout with view container and back button bar
    LuIStandardLayout layout = CreateStandardLayout();
    
    // Main view here
    Buffer * testBuffer=new Buffer(testImageBackground.width,testImageBackground.height);
    // get the buffer
    TFT_eSprite * buffImg = testBuffer->GetBuffer();
    // fill with awesome image :D
    buffImg->pushImage(0,0,testImageBackground.width,testImageBackground.height,(uint16_t *)testImageBackground.pixel_data);

    layout.viewContainer->AddChild(testBuffer);
    testBuffer->dirty=true;

    AddChild(layout.screen);
    directDraw=true; // allow controls to direct redraw itself instead of push whole view Sprite
    // Thats all! the app is running
}
