#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <Encoder.h>
#include <avr/dtostrf.h>
#include "NavigationController.h"
#include "ViewControllers/Menus/MenuViewController.h"
#include "ViewControllers/Grinding/ManualGrindViewController.h"
#include "ViewControllers/Settings/PurgeTimeSettingViewController.h"
#include "ViewControllers/Settings/GrindTimeSettingViewController.h"
#include "ViewControllers/Settings/GrindTargetWeightSettingViewController.h"
#include "ViewControllers/Settings/ReactionTimeSettingViewController.h"
#include "ViewControllers/Grinding/GravimetricGrindViewController.h"
#include "ViewControllers/Settings/ProductivitySettingViewController.h"
#include "ViewControllers/Settings/CalibrationViewController.h"
#include "ViewControllers/Grinding/PurgeViewController.h"
#include "ViewControllers/Grinding/TimedGrindViewController.h"
#include "ViewControllers/ScaleViewController.h"
#include "ViewControllers/Menus/MenuItem/ViewControllerMenuItem.h"
#include "ViewControllers/Menus/MenuItem/PopNavigationAndCommitEEPROMMenuItem.h"
#include "ViewControllers/Menus/MenuItem/PurgeMenuItem.h"
#include "ViewControllers/Menus/MenuItem/GrindMenuItem.h"
#include "ViewControllers/Menus/MenuItem/GrindByWeightMenuItem.h"
#include "Settings.h"
#include "ScaleWrapper.h"
#include "ViewControllers/ButtonEvent.h"

const int Encoder_SW_Pin = 4;
const int Encoder_DT_Pin = 3; // Must be interrupt pin
const int Encoder_CLK_Pin = 2; // Must be interrupt pin
const int Manual_Grind_Pin = 14;
const int Ssr_Pin = 15;
const int Scale_DOUT_Pin = 9;
const int Scale_CLK_Pin = 10;

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int Encoder_SW_State = 0;
long Encoder_Diff = 0;
int Manual_Grind_State = HIGH;

long Old_Encoder_Position  = 0;

unsigned long Button_Press_Started_At = 0;

ButtonEvent currentButtonEvent = BUTTON_INACTIVE;

Encoder myEnc(Encoder_DT_Pin, Encoder_CLK_Pin);

ScaleWrapper* scale;
SsrState* ssr = nullptr;
ManualGrindViewController* manualGrindView = nullptr;
NavigationController* nav = nullptr;

void setup(void) {
//    delay(1000);

    pinMode(Manual_Grind_Pin, INPUT_PULLUP);
    pinMode(Encoder_SW_Pin, INPUT_PULLUP);

    u8g2.begin();
    Serial.begin(9600);

    ssr = new SsrState(Ssr_Pin);
    auto settings = new Settings();

    scale = ScaleWrapper::GetInstance(Scale_DOUT_Pin, Scale_CLK_Pin, settings);

    manualGrindView = new ManualGrindViewController(ssr);

    auto settingsMenu = new MenuViewController(std::vector<MenuItem*> {{
            new ViewControllerMenuItem("Purge time", new PurgeTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Grind time", new GrindTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Target weight", new GrindTargetWeightSettingViewController(settings)),
            new ViewControllerMenuItem("Reaction time", new ReactionTimeSettingViewController(settings)),
            new ViewControllerMenuItem("Productivity", new ProductivitySettingViewController(settings)),
            new ViewControllerMenuItem("Calibrate (100 g)", new CalibrationViewController(settings, scale)),
            new PopNavigationAndCommitEEPROMMenuItem("Back", settings)
    }});

    auto mainMenu = new MenuViewController(std::vector<MenuItem*> {{
            new PurgeMenuItem(new PurgeViewController(ssr, settings), settings),
            new GrindMenuItem(new TimedGrindViewController(ssr, settings), settings),
            new GrindByWeightMenuItem(new GravimetricGrindViewController(ssr, scale, settings), settings),
            new ViewControllerMenuItem("Scale", new ScaleViewController(scale)),
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

    if (Button_Press_Started_At == 0 && Encoder_SW_State == LOW) {
        Button_Press_Started_At = micros();
        currentButtonEvent = BUTTON_PRESS;
    } else if (Button_Press_Started_At > 0 && Encoder_SW_State == LOW) {
        currentButtonEvent = BUTTON_HOLD;
    } else if (Button_Press_Started_At > 0 && Encoder_SW_State == HIGH) {
        auto holdLength = micros() - Button_Press_Started_At;
        if (holdLength > 200000) {
            currentButtonEvent = BUTTON_PRESS_AND_HOLD_LET_UP;
        } else {
            currentButtonEvent = BUTTON_LET_UP;
        }
        Button_Press_Started_At = 0;
    } else { // (Button_Press_Started_At == 0 && Encoder_SW_State == HIGH) {
        currentButtonEvent = BUTTON_INACTIVE;
    }

    scale->refresh();
}

void loop(void) {
    //Serial.println(scale->getLatestValue());

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

    nav->top()->handleButtonEvent(currentButtonEvent);

    nav->top()->tick(u8g2);
}