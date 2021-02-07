#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <FlashAsEEPROM.h>
#include <Encoder.h>
#include "NavigationController.h"
#include "ViewControllers/MenuViewController.h"
#include "ViewControllers/ManualGrindViewController.h"
#include "ViewControllers/PurgeTimeSettingViewController.h"
#include "ViewControllers/GrindTimeSettingViewController.h"
#include "ViewControllers/ProductivitySettingViewController.h"
#include "ViewControllers/PurgeViewController.h"
#include "ViewControllers/TimedGrindViewController.h"
#include "MenuItem/ViewControllerMenuItem.h"
#include "MenuItem/PopNavigationAndCommitEEPROMMenuItem.h"
#include "MenuItem/PurgeMenuItem.h"
#include "MenuItem/GrindMenuItem.h"
#include "Settings.h"

const int Encoder_SW_Pin = 4;
const int Encoder_DT_Pin = 3; // Must be interrupt pin
const int Encoder_CLK_Pin = 2; // Must be interrupt pin
const int Manual_Grind_Pin = 14;
const int Ssr_Pin = 15;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int Encoder_SW_State = 0;
long Encoder_Diff = 0;
int Manual_Grind_State = HIGH;

long Old_Encoder_Position  = 0;

Encoder myEnc(Encoder_DT_Pin, Encoder_CLK_Pin);

SsrState* ssr = nullptr;
ManualGrindViewController* manualGrindView = nullptr;
NavigationController* nav = nullptr;

void setup(void) {
    delay(1000);

    pinMode(Manual_Grind_Pin, INPUT_PULLUP);
    pinMode(Encoder_SW_Pin, INPUT_PULLUP);

    u8g2.begin();
    Serial.begin(9600);

    ssr = new SsrState(Ssr_Pin);
    auto settings = new Settings(&EEPROM);

    manualGrindView = new ManualGrindViewController(ssr);

    auto settingsMenu = new MenuViewController(std::vector<MenuItem*> {{
            new ViewControllerMenuItem("Purge time", new PurgeTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Grind time", new GrindTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Productivity", new ProductivitySettingViewController(settings)),
            new PopNavigationAndCommitEEPROMMenuItem("Back", settings)
    }});

    auto mainMenu = new MenuViewController(std::vector<MenuItem*> {{
            new PurgeMenuItem(new PurgeViewController(ssr, settings), settings),
            new GrindMenuItem(new TimedGrindViewController(ssr, settings), settings),
            new ViewControllerMenuItem("Settings...", settingsMenu),
    }});

    nav = new NavigationController(mainMenu);
}

void updateExternalState() {
    Encoder_Diff = 0;
    long new_encoder_position = myEnc.read();
    if (new_encoder_position != Old_Encoder_Position) {
        Encoder_Diff = (new_encoder_position - Old_Encoder_Position);
        Old_Encoder_Position = new_encoder_position;
    }

    Encoder_SW_State = digitalRead(Encoder_SW_Pin);
    Manual_Grind_State = digitalRead(Manual_Grind_Pin);

}

void loop(void) {
    BaseViewController* top = nav->top();

    updateExternalState();

    // Handle manual grind state
    if (top != manualGrindView && Manual_Grind_State == LOW) {
        nav->push(manualGrindView);
    } else if (top == manualGrindView && Manual_Grind_State == HIGH) {
        nav->pop();
    }

    if (Encoder_Diff != 0) {
        nav->top()->handleRotation(Encoder_Diff);
    }

    nav->top()->handleButtonState(Encoder_SW_State == LOW);

    nav->top()->tick();

    nav->top()->render(u8g2);
}