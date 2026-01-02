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

#ifndef __LUNOKIOT__APPLICATION__SUPPORT__
#define __LUNOKIOT__APPLICATION__SUPPORT__
#include <Arduino.h>
#include "../UI/UI.hpp"
const uint8_t APPLICATIONCORE=UICORE;
//#include <Arduino.h>
//#include <TTGO.h>

//#include <libraries/TFT_eSPI/TFT_eSPI.h>
#ifdef LILYGO_DEV
#include <LilyGoWatch.h>
#endif

#ifdef M5_DEV
#include <M5Core2.h>
#include <M5Display.h>
#endif

#include <functional>
#include "../system/Datasources/perceptron.hpp"
#define tunable public // all settings accesable from outside
/*
 * Basic application with UI
 */
class LunokIoTApplication {
    public:
        bool                         dirty                    = false;                      // application dirty flag
        TFT_eSprite *                canvas;                  // application buffer (all must draw here)
        std::function<void(void*)>   backCallback             = nullptr;                    // callback to previous screen
        // build canvas
        LunokIoTApplication();
        virtual ~LunokIoTApplication();
        virtual bool Tick(); // the UI callback to manage input and screen
        //TFT_eSprite *ScreenCapture();
        virtual const bool isWatchface() { return false; } // used to determine if the app must be replaced with watchface when PEK button
        virtual const char *AppName() = 0; // app title
        virtual const bool mustShowAsTask() { return true; } // false=Not show in task switcher (menus and intermediate views must be hidden)
        virtual void LowMemory(); // called when system fails to allocate memory (malloc)
        void KeepScreenOn(); // reset screen timeout to prevent sleep
        //virtual RunApplicationCallback GetRunCallback();
};
typedef LunokIoTApplication* WatchfaceMaker();
template <class WFA> LunokIoTApplication* MakeWatch() { return new WFA; }
size_t WatchFacesAvailiable();
LunokIoTApplication *GetWatchFaceFromOffset(size_t off);
typedef std::function<LunokIoTApplication*()> RunApplicationCallback;

class LaunchApplicationDescriptor {
    public:
        LunokIoTApplication *   instance              = nullptr;  // application instance pointer
        bool                    animation             = false;    // enable launch animation
};

/*
 * Push the application to foreground
 */
void LaunchApplication(LunokIoTApplication *instance,bool animation=true,bool synced=false, bool force=false);
void LaunchWatchface(bool animation=false, bool force=false);
void LaunchApplicationTaskSync(LaunchApplicationDescriptor * appDescriptor,bool synched=false);

/*
 * Software keyboard is a special app
 */
enum lUIKeyboardType {
    KEYBOARD_NUMERIC,                   // 0~9
    KEYBOARD_ALPHANUMERIC_FREEHAND,     // draw letters to be recognize
//    KEYBOARD_PHONE,                   // phone dial
//    KEYBOARD_ALPHANUMERIC_SEQUENCE,   // old phone 3x3 buttons ABC-DEF-GHI.... sequence
//    KEYBOARD_HEXADECIMAL,             // usefull for old hex passwords
//    KEYBOARD_PATTERN,                 // unlock pattern 3x3/4x4...
//    KEYBOARD_NUMERIC_FREEHAND,        // draw numbers to OCR
//    KEYBOARD_IMAGE_DRAW,              // attach image instead of text
//    KEYBOARD_FULL_BLUETOOTH,          // use full keyboard bluetooth
};

//#include "../UI/widgets/EntryTextWidget.hpp"
#include "../UI/widgets/ButtonTextWidget.hpp"
#include "../UI/widgets/ButtonImageXBMWidget.hpp"

// base keyboard class
class SoftwareKeyboard : public LunokIoTApplication {
    public:
        char *                      textEntry             = nullptr;  // text entry buffer
        void *                      destinationWidget     = nullptr;  // target widget pointer
        
        const bool mustShowAsTask() final { return false; }
        SoftwareKeyboard(void * destinationWidget=nullptr);
        ~SoftwareKeyboard();
};

class SoftwareNumericKeyboard : public SoftwareKeyboard {
    public:
        uint8_t                 cursorBlinkStep       = 0;         // cursor blink animation step
        ButtonTextWidget *      seven                 = nullptr;   // button '7'
        ButtonTextWidget *      eight                 = nullptr;   // button '8'
        ButtonTextWidget *      nine                  = nullptr;   // button '9'
        ButtonTextWidget *      four                  = nullptr;   // button '4'
        ButtonTextWidget *      five                  = nullptr;   // button '5'
        ButtonTextWidget *      six                   = nullptr;   // button '6'
        ButtonTextWidget *      one                   = nullptr;   // button '1'
        ButtonTextWidget *      two                   = nullptr;   // button '2'
        ButtonTextWidget *      three                 = nullptr;   // button '3'
        ButtonTextWidget *      zero                  = nullptr;   // button '0'
        bool                    dotAdded              = false;     // decimal point added flag
        ButtonTextWidget *      dotBtn                = nullptr;   // decimal point button

        ButtonImageXBMWidget *  btnCancel             = nullptr;   // cancel button
        ButtonImageXBMWidget *  btnDiscard            = nullptr;   // discard button
        ButtonImageXBMWidget *  btnSend               = nullptr;   // send/confirm button
        //TFT_eSprite * destinationCanvas=nullptr;
        SoftwareNumericKeyboard(void * destinationWidget=nullptr );
        ~SoftwareNumericKeyboard();
        bool Tick() override;
        const char *AppName() override { return "Software numeric keyboard"; }
};

extern const char FreehandKeyboardLetterTrainableSymbols[];
extern const size_t FreehandKeyboardLetterTrainableSymbolsCount;

class SoftwareFreehandKeyboard : public SoftwareKeyboard {
    public:
        SoftwareFreehandKeyboard(void * destinationWidget=nullptr );
        ~SoftwareFreehandKeyboard();
        bool Tick() override;
        const char *AppName() override { return "Software freehand keyboard"; }
        Perceptron **perceptrons;
    private:
        unsigned long           nextRefresh_           = 0;                            // refresh timer
        unsigned long           oneSecond              = 0;                            // trigger clear pad
        int16_t                 boxX                   = TFT_WIDTH;                    // draw box X coordinate
        int16_t                 boxY                   = TFT_HEIGHT;                   // draw box Y coordinate
        int16_t                 boxH                   = 0;                            // draw box height
        int16_t                 boxW                   = 0;                            // draw box width
        bool                    triggered              = false;                        // launch recognizer flag
        TFT_eSprite *           perceptronCanvas       = nullptr;                      // perceptron rendering canvas
        TFT_eSprite *           freeHandCanvas         = nullptr;                      // freehand drawing canvas

        const uint8_t           PerceptronMatrixSize   = 11;                           // perceptron matrix size
        const int16_t           MINIMALDRAWSIZE        = PerceptronMatrixSize*4;       // minimum drawable size
        void Cleanup();
        void RedrawMe();
        void RemovePerceptron(Perceptron * item);
        Perceptron * LoadPerceptronFromSymbol(char symbol);
        Perceptron * BuildBlankPerceptron();
        /*
        const size_t BufferTextMax=20;
        char * bufferText=nullptr;
        size_t bufferTextOffset=0;
        */
        ButtonImageXBMWidget * btnCancel=nullptr;
        ButtonImageXBMWidget * btnDiscard=nullptr;
        ButtonImageXBMWidget * btnSend=nullptr;
};

#endif
